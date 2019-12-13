#pragma once

namespace Engine
{
	class UniformBuffer
	{
	public:
		virtual ~UniformBuffer() {}

		virtual void bind() const = 0;

		virtual void unbind() const = 0;

		static Ref<UniformBuffer> Create();
	};
}
