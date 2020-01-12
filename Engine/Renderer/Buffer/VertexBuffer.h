#pragma once

#include "BufferLayout.h"

namespace Engine
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer();

		static Ref<VertexBuffer> Create(float* vertices, unsigned int size);
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	
		virtual const BufferLayout& GetLayout() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
	protected:
		VertexBuffer();
		BufferLayout mLayout;
	};
}
