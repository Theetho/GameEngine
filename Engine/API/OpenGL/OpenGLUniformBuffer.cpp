#include "EnginePch.h"
#include "OpenGLUniformBuffer.h"

namespace Engine
{
	OpenGLUniformBuffer::OpenGLUniformBuffer()
	{
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
	}

	void OpenGLUniformBuffer::Bind() const
	{
		glBindBuffer(GL_UNIFORM_BUFFER, mId);
	}

	void OpenGLUniformBuffer::Unbind() const
	{
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}