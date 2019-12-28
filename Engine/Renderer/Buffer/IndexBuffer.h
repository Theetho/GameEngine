#pragma once

namespace Engine
{
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer();

		static Ref<IndexBuffer> Create(unsigned int* indices, unsigned int count);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual unsigned int GetCount() const = 0;
	};
}
