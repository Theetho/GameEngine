#include "EnginePch.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Buffer/VertexBuffer.h"
#include "Renderer/Buffer/IndexBuffer.h"
#include "Core/Camera3D.h"
#include "Core/AssetManager.h"
#include "Include/Maths.h"
#include "../RendererAPI/CRendererAPI.h"

#include "CRenderer.h"

namespace Engine
{
	// Definitions

	template<int dimension>
	std::shared_ptr<CRendererAPI> CRenderer<dimension>::_sRenderer;

	template<int dimension>
	inline CRenderer<dimension>::CRenderer()
		: _mVertexArray(nullptr)
		, _mVertexBuffer(nullptr)
		, _mIndexBuffer(nullptr)
		, _mTextures()
		, _mBuffer()
		, _mIndices()
	{}

	template<int dimension>
	void CRenderer<dimension>::_Initialize()
	{
		// Query the renderer
		if (!_sRenderer)
		{
			_sRenderer = CRendererAPI::_Get();
		}
		// Query the maximum texture units
		_mData.max_texture_units = _sRenderer->_GetMaxTextureUnits();

		_mVertexBuffer = VertexBuffer::Create(nullptr, _mData.max_vertex_renderable, BufferUsage::DYNAMIC);
		_mVertexBuffer->SetLayout(BufferLayout({
			BufferElement(dimension == 2 ? ShaderDataType::Float2 : ShaderDataType::Float3, "inPosition"),
			BufferElement(ShaderDataType::Float2, "inTextureCoords"),
			BufferElement(ShaderDataType::Float4, "inColor"),
			BufferElement(ShaderDataType::Float,  "inTextureID"),
			}));
		_mIndexBuffer = IndexBuffer::Create(nullptr, 6 * _mData.max_vertex_renderable, BufferUsage::DYNAMIC);

		_mVertexArray = VertexArray::Create();
		_mVertexArray->AddIndexBuffer(_mIndexBuffer);
		_mVertexArray->AddVertexBuffer(_mVertexBuffer);

		_mBuffer = std::move(std::vector<Vertex<dimension>>(_mData.max_vertex_renderable));

		// Loading shader
		_mShader = AssetManager::GetShaderLibrary().Load(
			"basic" + std::to_string(dimension) + "D_" + std::to_string(_mData.max_texture_units) + "tex.glsl"
		);
	}

	template<int dimension>
	inline std::unordered_map<unsigned int, float> CRenderer<dimension>::_SubmitTextures(const std::vector<std::shared_ptr<Texture2D>>& textures)
	{
		// If their is no texture, we return the location of the
		// white texture
		if (!textures.size())
			return { };

		std::unordered_map<unsigned int, float> result;

		// Check if the new textures can be rendered now or later or at all
		int status = this->_RenderIfToMuchData(_mTextures.size(), textures.size(), _mData.max_texture_units);
		// At all
		if (status < 0)
		{
			ENGINE_LOG_ERROR("To much textures in this renderable\
				 : a renderable can't have more than {0} textures"
				, _mData.max_texture_units);
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
				for (unsigned int i = 0; i < _mTextures.size(); ++i)
				{
					if (_mTextures[i] != new_texture)
						continue;

					result[new_texture->GetId()] = i;
					found = true;
					break;
				} // And in that case retrieve its id

				if (found)
					continue;

				// Else we add it and also retrieve its id
				_mTextures.push_back(new_texture);
				result[new_texture->GetId()] = _mTextures.size() - 1.0f;
			}
		}

		return result;
	}

	template<int dimension>
	inline void CRenderer<dimension>::_Submit(CRenderable<dimension>* renderable)
	{
		// Check if the new data can be rendered now or later or at all
		if (this->_RenderIfToMuchData(_mBuffer.size(), renderable->_GetVertices().size(), _mData.max_vertex_renderable) < 0)
		{
			ENGINE_LOG_ERROR("To much vertices in this renderable\
				 : a renderable can't have more than {0} vertices"
				, _mData.max_vertex_renderable);
			return;
		}

		for (auto& vertex : renderable->_GetVertices())
		{
			// Convert vertices' local texture ids to the texture
			// id used in the shader
			auto texture_ids = this->_SubmitTextures(renderable->_GetTextures());

			_mBuffer[_mData.buffer_index].position			  = vertex.position;
			_mBuffer[_mData.buffer_index].color				  = vertex.color;
			_mBuffer[_mData.buffer_index].texture_coordinates = vertex.texture_coordinates;
			if (texture_ids.size())
				_mBuffer[_mData.buffer_index].texture_id = texture_ids[vertex.texture_id];
			else
				_mBuffer[_mData.buffer_index].texture_id = 0.0f;

			++_mData.buffer_index;
		}

		for (auto& indice : renderable->_GetIndices())
		{
			_mIndices.push_back(indice);
		}
	}

	template<int dimension>
	inline void CRenderer<dimension>::_BeginScene(Camera* camera)
	{
		_mSceneData.view = &camera->GetView();
		_mSceneData.projection = &camera->GetProjection();
		_mSceneData.vp = &camera->GetViewProjection();
		_mSceneData.camera_position = &camera->GetPosition();
	}

	template<int dimension>
	inline void CRenderer<dimension>::_EndScene()
	{
		_mSceneData.view = nullptr;
		_mSceneData.projection = nullptr;
		_mSceneData.vp = nullptr;
		_mSceneData.camera_position = nullptr;
		_mSceneData.cliping_plane = Vec4();
	}

	template<int dimension>
	inline void CRenderer<dimension>::_Begin()
	{
		_mShader->Bind();
		/// Upload uniforms

		for (unsigned int i = 0; i < _mTextures.size(); ++i)
			_mTextures[i]->Bind(i);

		_mVertexArray->Bind();
		_mVertexBuffer->SetData(reinterpret_cast<float*>(_mBuffer.data()));
		_mIndexBuffer->SetData(_mIndices.data());
	}

	template<int dimension>
	inline void CRenderer<dimension>::_Render()
	{
		_Begin();
		_sRenderer->_Draw(_mVertexArray);
		_End();
	}

	template<int dimension>
	inline void CRenderer<dimension>::_End()
	{
		_mBuffer.clear();
		_mBuffer = std::move(std::vector<Vertex<dimension>>(_mData.max_vertex_renderable));
		_mData.buffer_index = 0;

		_mIndices.clear();

		_mTextures.clear();
		_mTextures.push_back(Texture2D::GetWhiteTexture());
	}

	template<int dimension>
	inline int CRenderer<dimension>::_RenderIfToMuchData(unsigned int current, unsigned int addition, unsigned int total)
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
				_Render();
				return 1;
			}
		}
		return 0;
	}

	template class CRenderer<2>;
	template class CRenderer<3>;
}
