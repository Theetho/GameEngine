#include "EnginePch.h"
#include "OpenGLVertexBuffer.h"

namespace Engine
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(
		float* vertices,
		const unsigned int& count
	)
		: m_id(0)
		, m_layout({})
	{
		glCreateBuffers(1, &m_id);

		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);
	}
	
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}
}