#include "EnginePch.h"
#include "VertexBuffer.h"
#include "BufferLayout.h"
#include "Renderer/Rendering/Renderer.h"
#include "Renderer/Rendering/RendererAPI.h"
#include "API/OpenGL/VertexBuffer.h"

namespace Engine
{
	VertexBuffer::~VertexBuffer()
	{}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint vertex_count, BufferUsage buffer_usage)
	{
		switch (Renderer::GetAPI())
		{
		case Engine::API::None:
			ENGINE_ASSERT(false, "Api not supported");
		case Engine::API::OpenGL:
			return CreateRef<OpenGL::VertexBuffer>(vertices, vertex_count, buffer_usage);
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

	const BufferLayout& VertexBuffer::GetLayout() const
	{
		return mLayout;
	}

	void VertexBuffer::SetLayout(const BufferLayout& layout)
	{
		mLayout = layout;
	}
}