#pragma once

#include "Renderer/Buffer/IndexBuffer.h"

namespace Engine
{
	namespace OpenGL
	{
		class IndexBuffer : public Engine::IndexBuffer
		{
		public:
			IndexBuffer(unsigned int* indices, unsigned int count);
			~IndexBuffer();

			void Bind() const override;
			void Unbind() const override;
			unsigned int GetCount() const override;
		private:
			unsigned int mId;
			unsigned int mCount;
		};
	}
}
