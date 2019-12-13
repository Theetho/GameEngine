#include "EnginePch.h"
#include "VertexArray.h"
#include "Renderer/Rendering/Renderer.h"
#include "API/OpenGL/OpenGLVertexArray.h"

namespace Engine
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::getAPI())
		{
		case Engine::API::None:
			ENGINE_ASSERT(false, "Api not supported");
		case Engine::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		}

		return nullptr;
	}
}