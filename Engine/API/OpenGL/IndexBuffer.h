#pragma once

#include "Renderer/Buffer/IndexBuffer.h"
#include "GLBuffer.h"

namespace Engine
{
	namespace OpenGL
	{
		class IndexBuffer : public Engine::IndexBuffer, private Buffer<GL_ELEMENT_ARRAY_BUFFER, uint>
		{
		public:
			IndexBuffer(uint* indices, uint indices_count, BufferUsage buffer_usage = BufferUsage::STATIC);

			void Bind() const override;
			void Unbind() const override;
			void SetData(uint* data) override;
		};
	}
}
