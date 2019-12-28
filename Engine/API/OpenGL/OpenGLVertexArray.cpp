#include "EnginePch.h"
#include "OpenGLVertexArray.h"
#include "Renderer/Rendering/Renderer.h"

namespace Engine
{
	OpenGLVertexArray::OpenGLVertexArray()
		: mId(0)
	{
		glCreateVertexArrays(1, &mId);
		glBindVertexArray(mId);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &mId);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(mId);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
	
	void OpenGLVertexArray::AddVertexBuffer(Ref<VertexBuffer> vertex_buffer)
	{
		glBindVertexArray(mId);
		vertex_buffer->Bind();

		ENGINE_ASSERT(vertex_buffer->GetLayout().GetElements().size(), "Vbo has no layout");

		unsigned int index = 0;

		const auto& layout = vertex_buffer->GetLayout();

		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index++,
				element.GetElementCount(),
				ShaderDataTypeToGLType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.offset
			);
		}

		mVertexBuffers.push_back(vertex_buffer);
	}
	
	void OpenGLVertexArray::AddIndexBuffer(Ref<IndexBuffer> ibo)
	{
		glBindVertexArray(mId);
		ibo->Bind();

		mIndexBuffer = ibo;
	}
}