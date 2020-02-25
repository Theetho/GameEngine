#pragma once

#include "BufferUtil.h"

namespace Engine
{
	class IndexBuffer
	{
	public:
		IndexBuffer(uint indices_count);
		virtual ~IndexBuffer();

		static Ref<IndexBuffer> Create(uint* indices, uint indices_count, BufferUsage buffer_usage = BufferUsage::STATIC);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void SetData(uint* data) = 0;

		uint GetCount() const;
	protected:
		uint mCount;
	};
}
