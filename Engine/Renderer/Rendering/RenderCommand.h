#pragma once

namespace Engine
{
	class RendererAPI;
	enum class API;
	class VertexArray;

	class RenderCommand
	{
	public:
		static API GetAPI();
		static void SetViewport(unsigned int width, unsigned int height);
		static void SetClearColor(const Color& color);
		static void Clear();
		static void DrawIndexed(const VertexArray& vertex_array);
		static void DrawIndexed(Ref<VertexArray> vertex_array);
	private:
		static RendererAPI* sRenderer;
	};
}

