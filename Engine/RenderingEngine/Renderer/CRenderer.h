#pragma once

#include "../Renderable/CRenderable.h"

namespace Engine
{
	class RenderingPipeline;
	class Camera3D;
	using Camera = Camera3D;
	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;
	class Shader;
	class CRendererAPI;

	template<int dimension>
	struct CRendererData
	{
		const int max_vertex_renderable = 10000;
		const int vertex_size = sizeof(Vertex<dimension>);
		const int float_in_one_vertex = dimension + 7;
		const int total_float_in_buffer = max_vertex_renderable * float_in_one_vertex;
		uint max_texture_units = 1;
	};

	struct CRendererSceneData
	{
		const Mat4* view;
		const Mat4* projection;
		const Mat4* vp;
		const Vec3* camera_position;
		Vec4  cliping_plane;
	};

	template<int dimension>
	class CRenderer
	{
	public:
		void _Submit(CRenderable<dimension>* renderable);
		void _BeginScene(Camera* camera);
		void _Render();
		void _EndScene();
	private:
		friend class RenderingPipeline;

		// Renderer that make link between the engine and the API
		static std::shared_ptr<CRendererAPI> _sRenderer;
		// Attributes used in the draw call
		std::shared_ptr<VertexArray>  _mVertexArray;
		std::shared_ptr<IndexBuffer>  _mIndexBuffer;
		std::shared_ptr<VertexBuffer> _mVertexBuffer;
		std::shared_ptr<Shader>		  _mShader;
		// Copy of the data to be render

		///std::vector<Vertex<dimension>> _mBuffer;
		std::vector<float> _mBuffer;
		std::vector<unsigned int>	   _mIndices;
		// Textures to send to the shaders (usualy 32 max)
		std::vector<std::shared_ptr<Texture2D>> _mTextures;

		// Struct that stores some constants
		CRendererData<dimension> _mData;
		CRendererSceneData		 _mSceneData;

		CRenderer();
		void _Initialize();
		void _Begin();
		void _End();
		// Add the textures to the vector, if they are not already in it
		// and return a map between local and actual texture ids
		std::unordered_map<unsigned int, float> _SubmitTextures(const std::vector<std::shared_ptr<Texture2D>>& textures);
		// @return : # 1 if the data was rendered
		//	 # 0 if it was not rendered but it can be on an other draw call
		//	 # -1 if it was not rendered and it cannot be (error, see console)
		int _RenderIfToMuchData(unsigned int current, unsigned int addition, unsigned int total);
	};

	using CRenderer2D = CRenderer<2>;
	using CRenderer3D = CRenderer<3>;
}

