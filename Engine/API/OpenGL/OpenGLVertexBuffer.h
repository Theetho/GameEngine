#pragma once

#include "Renderer/Buffer/VertexBuffer.h"

namespace Engine
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(
			float* vertices, 
			const unsigned int& count
		);
		
		~OpenGLVertexBuffer();

		inline void bind() const override
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_id);
		}
		
		inline void unbind() const override
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		inline void setLayout(
			const BufferLayout& layout
		) override
		{
			m_layout = layout;
		}

		inline const BufferLayout& getLayout() const override
		{
			return m_layout;
		}
	private:
		unsigned int m_id;
		BufferLayout m_layout;
	};
}
