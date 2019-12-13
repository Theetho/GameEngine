#include "EnginePch.h"
#include "RendererAPI.h"

namespace Engine
{
	API RendererAPI::s_api;

	OpenGLRenderer::OpenGLRenderer()
	{
		s_api = API::OpenGL;
	}

	OpenGLRenderer::~OpenGLRenderer()
	{
	}
}
