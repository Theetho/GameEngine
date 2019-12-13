#include "EnginePch.h"
#include "UniformBuffer.h"
#include "Renderer/Rendering/Renderer.h"
#include "API/OpenGL/OpenGLUniformBuffer.h"

namespace Engine
{
	Ref<UniformBuffer> UniformBuffer::Create()
	{
		switch (Renderer::getAPI())
		{
			case Engine::API::None:
				ENGINE_ASSERT(false, "Api not supported");
			case Engine::API::OpenGL:
				return std::make_shared<OpenGLUniformBuffer>();
		}
	}
}