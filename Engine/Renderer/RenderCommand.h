#pragma once

#include "RendererAPI.h"

namespace Engine
{
	class RenderCommand
	{
	public:
		static inline API getAPI()
		{
			return RendererAPI::s_api;
		}
		
		static void setClearColor(
			const Color& color
		);
		
		static void clear();

		static void drawIndexed(
			const Ref<VertexArray>& vao
		);

	private:
		static RendererAPI* s_renderer;
	};
}

