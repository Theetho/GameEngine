#include "EnginePch.h"
#include "IndexBuffer.h"

namespace Engine
{
	namespace OpenGL
	{
		IndexBuffer::IndexBuffer(uint* indices, uint indices_count, BufferUsage buffer_usage)
			: Engine::IndexBuffer(indices_count)
			, Buffer(indices, indices_count, buffer_usage)
		{}

		void IndexBuffer::Bind() const
		{
			GLBind();
		}

		void IndexBuffer::Unbind() const
		{
			GLUnbind();
		}

		void IndexBuffer::SetData(std::vector<uint>& data)
		{
			GLSetData(data);
			mCount = data.size();
		}
	}
}