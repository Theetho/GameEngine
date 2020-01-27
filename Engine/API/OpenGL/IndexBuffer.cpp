#include "EnginePch.h"
#include "IndexBuffer.h"
#include "Renderer/Rendering/Renderer.h"

namespace Engine
{
	namespace OpenGL
	{
		IndexBuffer::IndexBuffer(unsigned int* indices, unsigned int count)
			: Engine::IndexBuffer()
			, mId(0)
			, mCount(count)
		{
			glCreateBuffers(1, &mId);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
		}

		IndexBuffer::~IndexBuffer()
		{
			glDeleteBuffers(1, &mId);
		}

		void IndexBuffer::Bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
		}

		void IndexBuffer::Unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		unsigned int IndexBuffer::GetCount() const
		{
			return mCount;
		}
	}
}