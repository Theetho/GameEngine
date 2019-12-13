#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Engine
{
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
			const Ref<IndexBuffer>& ibo
		) = 0;

		virtual inline const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const
		{
			return m_vbos;
		}
		
		virtual inline const Ref<IndexBuffer> getIndexBuffer() const
		{
			return m_ibo;
		}

		static Ref<VertexArray> Create();
	protected:
		std::vector<Ref<VertexBuffer>> m_vbos;
		Ref<IndexBuffer>			   m_ibo;
	};
}

