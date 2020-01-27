#include "EnginePch.h"
#include "UniformBuffer.h"

namespace Engine
{
	namespace OpenGL
	{
		UniformBuffer::UniformBuffer()
			: Engine::UniformBuffer()
		{
		}

		UniformBuffer::~UniformBuffer()
		{
		}

		void UniformBuffer::Bind() const
		{
			glBindBuffer(GL_UNIFORM_BUFFER, mId);
		}

		void UniformBuffer::Unbind() const
		{
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}
	}
}