#pragma once

namespace Engine
{
	class VertexArray;

	enum class API
	{
		None,
		OpenGL
	};
	enum class DrawMode
	{
		DEFAULT, TRIANGLES, TRIANGLE_STRIP, PATCHES
	};
	class RendererAPI
	{
	public:
		virtual ~RendererAPI();

		virtual void Clear() = 0;
		virtual void Draw(const VertexArray& vertex_array) = 0;

		virtual void SetDrawMode(DrawMode draw_mode) = 0;
		virtual void SetViewport(unsigned int width, unsigned int height) = 0;
		virtual void SetClearColor(const Color& color) = 0;

		static API sApi;
	protected:
		DrawMode mDrawMode;

		virtual unsigned int TranslateDrawMode() = 0;
	};
}

