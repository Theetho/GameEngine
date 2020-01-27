#include "EnginePch.h"
#include "IndexBuffer.h"
#include "Renderer/Rendering/Renderer.h"
#include "Renderer/Rendering/RendererAPI.h"
#include "API/OpenGL/IndexBuffer.h"

namespace Engine
{
	IndexBuffer::~IndexBuffer()
	{}

	Ref<IndexBuffer> IndexBuffer::Create(unsigned int* indices, unsigned int count)
	{
		switch (Renderer::GetAPI())
		{
			case Engine::API::None:
				ENGINE_ASSERT(false, "Api not supported");
			case Engine::API::OpenGL:
				return CreateRef<OpenGL::IndexBuffer>(indices, count);
		}
	}
}