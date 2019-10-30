#include "EnginePch.h"
#include "Buffer.h"
#include "Renderer.h"

namespace Engine
{

/// Abstract base classes

	// Buffer layout

	BufferLayout::BufferLayout(
		const std::initializer_list<BufferElement>& elements
	)
		: m_elements(elements)
		, m_stride(0)
	{
		this->calculateOffsetsAndStride();
	}
	
	void BufferLayout::calculateOffsetsAndStride()
	{
		unsigned int offset = 0;

		for (auto& element : m_elements)
		{
			element.offset = offset;
			offset		  += element.size;
			m_stride	  += element.size;
		}
	}

	// Vertex buffer

	Ref<VertexBuffer> VertexBuffer::create(
		float* vertices, 
		const unsigned int& size
	)
	{
		switch (Renderer::getAPI())
		{
		case Engine::API::None:
			ENGINE_ASSERT(false, "Api not supported");
		case Engine::API::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}
	}

	// Index buffer

	Ref<IndexBuffer> IndexBuffer::create(
		unsigned int* indices,
		const unsigned int& size
	)
	{
		switch (Renderer::getAPI())
		{
		case Engine::API::None:
			ENGINE_ASSERT(false, "Api not supported");
		case Engine::API::OpenGL:
			return std::make_shared<OpenGLIndexBuffer>(indices, size);
		}	
	}

/// OpenGL buffers

	// Vertex buffer

	OpenGLVertexBuffer::OpenGLVertexBuffer(
		float* vertices,
		const unsigned int& size
	)
		: m_id(0)
		, m_layout({})
	{
		glCreateBuffers(1, &m_id);

		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}

	// Index buffer

	OpenGLIndexBuffer::OpenGLIndexBuffer(
		unsigned int* indices,
		const unsigned int& count
	)
		: m_id(0)
		, m_count(count)
	{
		glCreateBuffers(1, &m_id);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	}
	
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}
}