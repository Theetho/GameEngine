#pragma once

#include "Renderer/Buffer/UniformBuffer.h"

namespace Engine
{
	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer();
		~OpenGLUniformBuffer();

		void Bind() const override;
		void Unbind() const override;
	private:
		unsigned int mId;
	};
}
