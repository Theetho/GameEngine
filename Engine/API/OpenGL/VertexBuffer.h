#pragma once

#include "Renderer/Buffer/VertexBuffer.h"
#include "GLBuffer.h"

namespace Engine
{
	namespace OpenGL
	{
		class VertexBuffer : public Engine::VertexBuffer, private Buffer<GL_ARRAY_BUFFER, float>
		{
		public:
			VertexBuffer(float* vertices, uint vertex_count, BufferUsage buffer_usage = BufferUsage::STATIC);

			void Bind() const override;
			void Unbind() const override;
			void SetData(std::vector<float>& data) override;
		};
	}
}
