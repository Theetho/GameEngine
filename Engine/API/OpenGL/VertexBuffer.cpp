#include "EnginePch.h"
#include "VertexBuffer.h"

namespace Engine
{
	namespace OpenGL
	{
		VertexBuffer::VertexBuffer(float* vertices, unsigned int vertex_count)
			: Engine::VertexBuffer(vertex_count)
			, mId(0)
		{
			glCreateBuffers(1, &mId);

			glBindBuffer(GL_ARRAY_BUFFER, mId);
			glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(float), vertices, GL_STATIC_DRAW);
		}

		VertexBuffer::~VertexBuffer()
		{
			glDeleteBuffers(1, &mId);
		}

		void VertexBuffer::Bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, mId);
		}

		void VertexBuffer::Unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}