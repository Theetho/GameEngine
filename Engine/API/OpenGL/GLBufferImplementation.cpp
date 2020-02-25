#include "EnginePch.h"
#include "GLBuffer.h"

namespace Engine
{
	namespace OpenGL
	{
		template<unsigned int type, class T>
		inline Buffer<type, T>::Buffer(T* data, unsigned int count, BufferUsage buffer_usage)
		{
			glCreateBuffers(1, &mId);

			glBindBuffer(type, mId);
			glBufferData(type, count * sizeof(T), data, GetBufferUsage(buffer_usage));
		}

		template<unsigned int type, class T>
		inline Buffer<type, T>::~Buffer()
		{
			glDeleteBuffers(1, &mId);
		}

		template<unsigned int type, class T>
		inline void Buffer<type, T>::GLBind() const
		{
			glBindBuffer(type, mId);
		}

		template<unsigned int type, class T>
		inline void Buffer<type, T>::GLUnbind() const
		{
			glBindBuffer(type, 0);
		}

		template<unsigned int type, class T>
		inline void Buffer<type, T>::GLSetData(T* data)
		{
			glBufferSubData(type, 0, sizeof(data), data);
		}

		template<unsigned int type, class T>
		inline unsigned int Buffer<type, T>::GetBufferUsage(BufferUsage buffer_usage) const
		{
			switch (buffer_usage)
			{
				case BufferUsage::STATIC: return GL_STATIC_DRAW; break;
				case BufferUsage::DYNAMIC: return GL_DYNAMIC_DRAW; break;
				default: return GL_STATIC_DRAW; break;
			}
		}

		template class Buffer<GL_ARRAY_BUFFER, float>;
		template class Buffer<GL_ELEMENT_ARRAY_BUFFER, unsigned int>;
	}
}