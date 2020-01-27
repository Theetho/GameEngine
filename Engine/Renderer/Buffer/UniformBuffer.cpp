#include "EnginePch.h"
#include "UniformBuffer.h"
#include "Renderer/Rendering/Renderer.h"
#include "Renderer/Rendering/RendererAPI.h"
#include "API/OpenGL/UniformBuffer.h"

namespace Engine
{
	UniformBuffer::~UniformBuffer()
	{}

	Ref<UniformBuffer> UniformBuffer::Create()
	{
		switch (Renderer::GetAPI())
		{
			case Engine::API::None:
				ENGINE_ASSERT(false, "Api not supported");
			case Engine::API::OpenGL:
				return CreateRef<OpenGL::UniformBuffer>();
		}
	}
}