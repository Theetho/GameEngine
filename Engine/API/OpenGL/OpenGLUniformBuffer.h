#pragma once

#include "Renderer/Buffer/UniformBuffer.h"

namespace Engine
{
	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer();
		
		~OpenGLUniformBuffer();

		inline void bind() const override
		{
			glBindBuffer(GL_UNIFORM_BUFFER, m_id);
		}

		inline void unbind() const override
		{
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}

	private:
		unsigned int m_id;
	};
}
