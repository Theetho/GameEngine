#include "EnginePch.h"
#include "VertexBuffer.h"

namespace Engine
{
	namespace OpenGL
	{
		VertexBuffer::VertexBuffer(float* vertices, uint vertex_count, BufferUsage buffer_usage)
			: Engine::VertexBuffer(vertex_count)
			, Buffer(vertices, vertex_count, buffer_usage)
		{}

		void VertexBuffer::Bind() const
		{
			GLBind();
		}

		void VertexBuffer::Unbind() const
		{
			GLUnbind();
		}

		void VertexBuffer::SetData(float* data)
		{
			GLSetData(data);
		}
	}
}