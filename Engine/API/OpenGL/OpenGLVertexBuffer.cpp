#include "EnginePch.h"
#include "OpenGLVertexBuffer.h"

namespace Engine
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, unsigned int count)
		: mId(0)
		, mLayout({})
	{
		glCreateBuffers(1, &mId);

		glBindBuffer(GL_ARRAY_BUFFER, mId);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);
	}
	
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &mId);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, mId);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	const BufferLayout& OpenGLVertexBuffer::GetLayout() const
	{
		return mLayout;
	}

	void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout)
	{
		mLayout = layout;
	}
}