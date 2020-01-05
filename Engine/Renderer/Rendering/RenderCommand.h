#pragma once

#include "RendererAPI.h"

namespace Engine
{
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

