#pragma once

#include "Renderer/Buffer/VertexBuffer.h"

namespace Engine
{
	namespace OpenGL
	{
		class VertexBuffer : public Engine::VertexBuffer
		{
		public:
			VertexBuffer(float* vertices, unsigned int vertex_count);
			~VertexBuffer();

			void Bind() const override;
			void Unbind() const override;
		private:
			unsigned int mId;
		};
	}
}
