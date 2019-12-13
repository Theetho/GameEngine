#pragma once

namespace Engine
{
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer()
		{
		}

		virtual void bind() const = 0;

		virtual void unbind() const = 0;

		virtual unsigned int getCount() const = 0;

		static Ref<IndexBuffer> Create(
			unsigned int* indices,
			const unsigned int& count
		);
	};
}
