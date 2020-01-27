#include "EnginePch.h"
#include "VertexArray.h"
#include "Renderer/Rendering/Renderer.h"
#include "Renderer/Buffer.h"

namespace Engine
{
	namespace OpenGL
	{
		VertexArray::VertexArray()
			: Engine::VertexArray()
			, mId(0)
		{
			glCreateVertexArrays(1, &mId);
			glBindVertexArray(mId);
		}

		VertexArray::~VertexArray()
		{
			glDeleteVertexArrays(1, &mId);
		}

		void VertexArray::Bind() const
		{
			glBindVertexArray(mId);
		}

		void VertexArray::Unbind() const
		{
			glBindVertexArray(0);
		}

		void VertexArray::AddVertexBuffer(Ref<VertexBuffer> vertex_buffer)
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

		void VertexArray::AddIndexBuffer(Ref<IndexBuffer> ibo)
		{
			glBindVertexArray(mId);
			ibo->Bind();

			mIndexBuffer = ibo;
		}
	}
}