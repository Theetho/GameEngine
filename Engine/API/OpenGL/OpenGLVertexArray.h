#pragma once

#include "Renderer/Buffer/VertexArray.h"

namespace Engine
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		
		~OpenGLVertexArray();

		inline void bind() const override
		{
			glBindVertexArray(m_id);
		}
		
		inline void unbind() const override
		{
			glBindVertexArray(0);
		}

		void addVertexBuffer(
			const Ref<VertexBuffer>& vbo
		) override;
		
		void addIndexBuffer(
			const Ref<IndexBuffer>& vbo
		) override;

	private:
		unsigned int m_id;
		unsigned int m_index = 0;
	};
}

