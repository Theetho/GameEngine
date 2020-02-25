#pragma once

#include "Renderer/Buffer/BufferUtil.h"

namespace Engine
{
	namespace OpenGL
	{
		template<unsigned int type, class T>
		class Buffer
		{
		protected:
			Buffer(T* data, unsigned int count, BufferUsage buffer_usage);
			virtual ~Buffer();
			void GLBind() const;
			void GLUnbind() const;
			void GLSetData(T* data);
			unsigned int GetBufferUsage(BufferUsage buffer_usage) const;

			unsigned int mId;
		};
	}
}

