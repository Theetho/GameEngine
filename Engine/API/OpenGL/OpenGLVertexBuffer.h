#pragma once

#include "Renderer/Buffer/VertexBuffer.h"

namespace Engine
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, unsigned int vertex_count);
		~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;
	private:
		unsigned int mId;
	};
}
