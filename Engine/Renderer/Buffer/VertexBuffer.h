#pragma once

#include "BufferLayout.h"

namespace Engine
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer();

		static Ref<VertexBuffer> Create(float* vertices, unsigned int vertex_count);
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	
		virtual const BufferLayout& GetLayout() const = 0;
		virtual unsigned int	    GetCount() const;

		virtual void SetLayout(const BufferLayout& layout) = 0;
	protected:
		unsigned int mCount;
		VertexBuffer(unsigned int vertex_count);
		BufferLayout mLayout;
	};
}
