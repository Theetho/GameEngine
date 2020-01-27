#pragma once

#include "Renderer/Buffer/UniformBuffer.h"

namespace Engine
{
	namespace OpenGL
	{
		class UniformBuffer : public Engine::UniformBuffer
		{
		public:
			UniformBuffer();
			~UniformBuffer();

			void Bind() const override;
			void Unbind() const override;
		private:
			unsigned int mId;
		};
	}
}
