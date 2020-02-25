#include "EnginePch.h"
#include "IndexBuffer.h"
#include "Renderer/Rendering/Renderer.h"
#include "Renderer/Rendering/RendererAPI.h"
#include "API/OpenGL/IndexBuffer.h"
#include "..\..\API\OpenGL\IndexBuffer.h"

namespace Engine
{
	IndexBuffer::IndexBuffer(uint indices_count)
		: mCount(indices_count)
	{}

	IndexBuffer::~IndexBuffer()
	{}

	Ref<IndexBuffer> IndexBuffer::Create(uint* indices, uint indices_count, BufferUsage buffer_usage)
	{
		switch (Renderer::GetAPI())
		{
			case Engine::API::None:
				ENGINE_ASSERT(false, "Api not supported");
			case Engine::API::OpenGL:
				return CreateRef<OpenGL::IndexBuffer>(indices, indices_count, buffer_usage);
		}
	}

	uint IndexBuffer::GetCount() const
	{
		return mCount;
	}
}