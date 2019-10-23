#pragma once

#include "Buffer.h"

namespace Engine
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo) = 0;
		virtual void addIndexBuffer(const std::shared_ptr<IndexBuffer>& vbo) = 0;

		virtual inline const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const
		{
			return m_vbos;
		}
		virtual inline const std::shared_ptr<IndexBuffer>				 getIndexBuffer() const
		{
			return m_ibo;
		}

		static VertexArray* create();
	protected:
		std::vector<std::shared_ptr<VertexBuffer>> m_vbos;
		std::shared_ptr<IndexBuffer>			   m_ibo;
	};

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

		void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo) override;
		void addIndexBuffer(const std::shared_ptr<IndexBuffer>& vbo) override;

	private:
		unsigned int							   m_id;
		unsigned int							   m_index = 0;
	};

}

