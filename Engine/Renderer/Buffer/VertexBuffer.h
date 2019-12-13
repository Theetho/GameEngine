#pragma once

#include "BufferLayout.h"

namespace Engine
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void bind() const = 0;
		
		virtual void unbind() const = 0;

		virtual void setLayout(
			const BufferLayout& layout
		) = 0;
		
		virtual const BufferLayout& getLayout() const = 0;

		static Ref<VertexBuffer> Create(
			float* vertices, 
			const unsigned int& count
		);
	};
}
