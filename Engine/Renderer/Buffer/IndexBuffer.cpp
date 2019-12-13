#include "EnginePch.h"
#include "IndexBuffer.h"
#include "Renderer/Rendering/Renderer.h"
#include "API/OpenGL/OpenGLIndexBuffer.h"

namespace Engine
{
	Ref<IndexBuffer> IndexBuffer::Create(
		unsigned int* indices,
		const unsigned int& count
	)
	{
		switch (Renderer::getAPI())
		{
			case Engine::API::None:
				ENGINE_ASSERT(false, "Api not supported");
			case Engine::API::OpenGL:
				return std::make_shared<OpenGLIndexBuffer>(indices, count);
		}
	}
}