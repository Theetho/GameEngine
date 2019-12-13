#include "EnginePch.h"
#include "OpenGLIndexBuffer.h"
#include "Renderer/Rendering/Renderer.h"

namespace Engine
{
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