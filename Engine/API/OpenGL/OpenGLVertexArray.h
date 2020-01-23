#pragma once

#include "Renderer/Buffer/VertexArray.h"

namespace Engine
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind() const override;
		void Unbind() const override;

		virtual void AddVertexBuffer(Ref<VertexBuffer> vertex_buffer) override;
		virtual void AddIndexBuffer(Ref<IndexBuffer> index_buffer) override;
	protected:
		unsigned int mId;
		unsigned int mIndex = 0;
	};
}

