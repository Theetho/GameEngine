#pragma once

namespace Engine
{
	class UniformBuffer
	{
	public:
		virtual ~UniformBuffer();

		static Ref<UniformBuffer> Create();

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};
}
