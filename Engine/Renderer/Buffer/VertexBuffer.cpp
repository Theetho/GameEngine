#include "EnginePch.h"
#include "VertexBuffer.h"
#include "BufferLayout.h"
#include "Renderer/Rendering/Renderer.h"
#include "Renderer/Rendering/RendererAPI.h"
#include "API/OpenGL/OpenGLVertexBuffer.h"

namespace Engine
{
	VertexBuffer::~VertexBuffer()
	{}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, unsigned int vertex_count)
	{
		switch (Renderer::GetAPI())
		{
		case Engine::API::None:
			ENGINE_ASSERT(false, "Api not supported");
		case Engine::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(vertices, vertex_count);
		}
	}

	unsigned int VertexBuffer::GetCount() const
	{
		return mCount;
	}

	VertexBuffer::VertexBuffer(unsigned int vertex_count)
		: mLayout({})
		, mCount(vertex_count)
	{
	}
}