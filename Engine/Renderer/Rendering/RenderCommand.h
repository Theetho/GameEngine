#pragma once

namespace Engine
{
	class RendererAPI;
	enum class API;
	enum class DrawMode;
	class VertexArray;

	class RenderCommand
	{
	public:
		static void SetDrawMode(DrawMode draw_mode);
		static API GetAPI();
		static void SetViewport(unsigned int width, unsigned int height);
		static void SetClearColor(const Color& color);
		static void Clear();
		static void Draw(const VertexArray& vertex_array);
		static void Draw(Ref<VertexArray> vertex_array);
	private:
		static RendererAPI* sRenderer;
	};
}

