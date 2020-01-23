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
	
		const BufferLayout& GetLayout() const;
		unsigned int	    GetCount() const;

		void SetLayout(const BufferLayout& layout);
	protected:
		unsigned int mCount;
		VertexBuffer(unsigned int vertex_count);
		BufferLayout mLayout;
	};
}
