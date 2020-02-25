#pragma once

#include "../Renderable/Renderable.h"
#include "../RendererAPI/OpenGL.h"
#include "Renderer/Buffer.h"
#include "Core/Camera3D.h"
#include "Renderer/Shader.h"

namespace Engine
{
	class RenderingPipeline;
	using Camera = Camera3D;

	template<int dimension>
	class CRenderer
	{
	public:
		void Submit(CRenderable<dimension>* renderable);
		void BeginScene(Camera* camera);
		void Render();
		void EndScene();
	private:
		friend class RenderingPipeline;

		// Renderer that make link between the engine and the API
		static Ref<CRendererAPI> sRenderer;
		// Attributes used in the draw call
		Ref<VertexArray>  mVertexArray;
		Ref<IndexBuffer>  mIndexBuffer;
		Ref<VertexBuffer> mVertexBuffer;
		Scope<Shader>	  mShader;
		// Copy of the data to be render

		std::vector<Vertex<dimension>> mBuffer;
		std::vector<uint>			   mIndices;
		// Textures to send to the shaders (usualy 32 max)
		std::vector<Ref<Texture2D>> mTextures;

		// Struct that stores some constants
		struct Data
		{
			const int max_vertex_renderable = 10000;
			const int vertex_size = sizeof(Vertex<dimension>);
			const int total_buffer_size = max_vertex_renderable * vertex_size;
			uint max_texture_units;
			uint buffer_index = 0;
		};
		Data mData;
		struct SceneData
		{
			const Mat4* view;
			const Mat4* projection;
			const Mat4* vp;
			const Vec3* camera_position;
			Vec4  cliping_plane;
		};
		SceneData mSceneData;

		CRenderer();
		void Begin();
		void End();
		// Add the textures to the vector, if they are not already in it
		// and return a map between local and actual texture ids
		std::unordered_map<uint, float> SubmitTextures(const std::vector<Ref<Texture2D>>& textures);
		// @return : # 1 if the data was rendered
		//	 # 0 if it was not rendered but it can be on an other draw call
		//	 # -1 if it was not rendered and it cannot be (error, see console)
		int RenderIfToMuchData(uint current, uint addition, uint total);
	};

	// Definitions

	template<int dimension>
	Ref<CRendererAPI> CRenderer<dimension>::sRenderer;

	template<int dimension>
	inline CRenderer<dimension>::CRenderer()
		: mVertexArray(nullptr)
		, mVertexBuffer(nullptr)
		, mIndexBuffer(nullptr)
		, mTextures()
		, mBuffer()
		, mIndices()
	{
		// Query the renderer
		if (!sRenderer)
		{
			sRenderer = CRendererAPI::Get();
		}
		// Query the maximum texture units
		mData.max_texture_units = sRenderer->GetMaxTextureUnits();

		mVertexBuffer = VertexBuffer::Create(nullptr, mData.max_vertex_renderable, BufferUsage::DYNAMIC);
		mVertexBuffer->SetLayout(BufferLayout({
			BufferElement(dimension == 2 ? ShaderDataType::Float2 : ShaderDataType::Float3, "inPosition"),
			BufferElement(ShaderDataType::Float2, "inTextureCoords"),
			BufferElement(ShaderDataType::Float4, "inColor"),
			BufferElement(ShaderDataType::Float, "inTextureID"),
		}));
		mIndexBuffer  = IndexBuffer::Create(nullptr, 6 * mData.max_vertex_renderable, BufferUsage::DYNAMIC);
		
		mVertexArray  = VertexArray::Create();
		mVertexArray->AddIndexBuffer(mIndexBuffer);
		mVertexArray->AddVertexBuffer(mVertexBuffer);
		
		mBuffer = std::move(std::vector<Vertex<dimension>>(mData.max_vertex_renderable));
	}
	
	template<int dimension>
	inline std::unordered_map<uint, float> CRenderer<dimension>::SubmitTextures(const std::vector<Ref<Texture2D>>& textures)
	{
		// If their is no texture, we return the location of the
		// white texture
		if (!textures.size())
			return { };

		std::unordered_map<uint, float> result;

		// Check if the new textures can be rendered now or later or at all
		int status = this->RenderIfToMuchData(mTextures.size(), textures.size(), mData.max_texture_units);
		// At all
		if (status < 0)
		{
			ENGINE_LOG_ERROR("To much textures in this renderable\
				 : a renderable can't have more than {0} textures"
				, mData.max_texture_units);
			return { };
		}
		// Now or later
		else
		{
			// For each new texture
			for (auto new_texture : textures)
			{
				bool found = false;

				// We check if it was already in registered
				for (uint i = 0; i < mTextures.size(); ++i)
				{
					if (mTextures[i] != new_texture)
						continue;

					result[new_texture->GetId()] = i;
					found = true;
					break;
				} // And in that case retrieve its id

				if (found)
					continue;

				// Else we add it and also retrieve its id
				mTextures.push_back(new_texture);
				result[new_texture->GetId()] = mTextures.size() - 1.0f;
			}
		}
		
		return result;
	}

	template<int dimension>
	inline void CRenderer<dimension>::Submit(CRenderable<dimension>* renderable)
	{
		// Check if the new data can be rendered now or later or at all
		if (this->RenderIfToMuchData(mBuffer.size(), renderable->GetVertices().size(), mData.max_vertex_renderable) < 0)
		{
			ENGINE_LOG_ERROR("To much vertices in this renderable\
				 : a renderable can't have more than {0} vertices"
				, mData.max_vertex_renderable);
			return;
		}

		for (auto& vertex : renderable->GetVertices())
		{
			// Convert vertices' local texture ids to the texture
			// id used in the shader
			auto texture_ids = this->SubmitTextures(renderable->GetTextures());
			
			mBuffer[mData.buffer_index].position			= vertex.position;
			mBuffer[mData.buffer_index].color				= vertex.color;
			mBuffer[mData.buffer_index].texture_coordinates = vertex.texture_coordinates;
			if (texture_ids.size())
				mBuffer[mData.buffer_index].texture_id		= texture_ids[vertex.texture_id];
			else
				mBuffer[mData.buffer_index].texture_id		= 0.0f;
			
			++mData.buffer_index;
		}

		for (auto& indice : renderable->GetIndices())
		{
			mIndices.push_back(indice);
		}
	}

	template<int dimension>
	inline void CRenderer<dimension>::BeginScene(Camera* camera)
	{
		mSceneData.view			   = &camera->GetView();
		mSceneData.projection	   = &camera->GetProjection();
		mSceneData.vp			   = &camera->GetViewProjection();
		mSceneData.camera_position = &camera->GetPosition();
	}

	template<int dimension>
	inline void CRenderer<dimension>::EndScene()
	{
		mSceneData.view			   = nullptr;
		mSceneData.projection	   = nullptr;
		mSceneData.vp			   = nullptr;
		mSceneData.camera_position = nullptr;
		mSceneData.cliping_plane   = Vec4();
	}

	template<int dimension>
	inline void CRenderer<dimension>::Begin()
	{
		mShader->Bind();
		/// Upload uniforms

		for (uint i = 0; i < mTextures.size(); ++i)
			mTextures[i]->Bind(i);

		mVertexArray->Bind();
		auto x = mBuffer.data();
		mVertexBuffer->SetData(reinterpret_cast<float*>(mBuffer.data()));
		mIndexBuffer->SetData(mIndices.data());
	}

	template<int dimension>
	inline void CRenderer<dimension>::Render()
	{
		Begin();
		sRenderer->Draw(mVertexArray);
		End();
	}
	
	template<int dimension>
	inline void CRenderer<dimension>::End()
	{
		mBuffer.clear();
		mBuffer = std::move(std::vector<Vertex<dimension>>(mData.max_vertex_renderable));
		mData.buffer_index = 0;

		mIndices.clear();

		mTextures.clear();
		mTextures.push_back(Texture2D::GetWhiteTexture());
	}

	template<int dimension>
	inline int CRenderer<dimension>::RenderIfToMuchData(uint current, uint addition, uint total)
	{
		if (current + addition > total)
		{
			// Two cases : either the renderable has to much vertices or
			// textures on its own
			if (addition > total)
			{
				return -1;
			}
			// Or it can be drawn but on an other draw call so we draw
			// the existing data and then clear it
			else
			{
				Render();
				return 1;
			}
		}
		return 0;
	}

	using CRenderer2D = CRenderer<2>;
	using CRenderer3D = CRenderer<3>;
}

