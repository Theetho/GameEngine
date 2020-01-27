#pragma once

#include "Renderer/Buffer/VertexArray.h"

namespace Engine
{
	namespace OpenGL
	{
		class VertexArray : public Engine::VertexArray
		{
		public:
			VertexArray();
			~VertexArray();

			void Bind() const override;
			void Unbind() const override;

			virtual void AddVertexBuffer(Ref<Engine::VertexBuffer> vertex_buffer) override;
			virtual void AddIndexBuffer(Ref<Engine::IndexBuffer> index_buffer) override;
		protected:
			unsigned int mId;
			unsigned int mIndex = 0;
		};
	}
}

