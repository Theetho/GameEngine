#pragma once

#include "Renderer/Buffer/IndexBuffer.h"

namespace Engine
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(
			unsigned int* indices,
			const unsigned int& count);
		
		~OpenGLIndexBuffer();

		inline void bind() const override
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		}
		
		inline void unbind() const override
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		inline unsigned int getCount() const override
		{
			return m_count;
		}
	private:
		unsigned int m_id;
		unsigned int m_count;
	};
}
