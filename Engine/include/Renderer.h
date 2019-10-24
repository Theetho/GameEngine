#pragma once
#include "Export.h"

namespace Engine
{
	enum class RendererAPI
	{
		None,
		OpenGL
	};

	class Renderer
	{
	public:
		static RendererAPI s_api;
		inline static RendererAPI getAPI()
		{
			return s_api;
		}
	};
}

