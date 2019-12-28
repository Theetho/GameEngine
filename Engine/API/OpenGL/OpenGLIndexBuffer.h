#pragma once

#include "Renderer/Buffer/IndexBuffer.h"

namespace Engine
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
		~OpenGLIndexBuffer();

		void Bind() const override;
		void Unbind() const override;
		unsigned int GetCount() const override;
	private:
		unsigned int mId;
		unsigned int mCount;
	};
}
