#pragma once

#include "Buffer.h"

namespace Engine
{

/// Abstract base class

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void bind() const = 0;

		virtual void unbind() const = 0;

		virtual void addVertexBuffer(
			const Ref<VertexBuffer>& vbo
		) = 0;

		virtual void addIndexBuffer(
			const Ref<IndexBuffer>& vbo
		) = 0;

		virtual inline const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const
		{
			return m_vbos;
		}
		
		virtual inline const Ref<IndexBuffer>				 getIndexBuffer() const
		{
			return m_ibo;
		}

		static VertexArray* create();
	protected:
		std::vector<Ref<VertexBuffer>> m_vbos;
		Ref<IndexBuffer>			   m_ibo;
	};

/// OpenGL vertex array

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

