#pragma once

#include "Renderer/Buffer/FrameBuffer.h"

namespace Engine
{
	namespace OpenGL
	{
		class FrameBuffer : public Engine::FrameBuffer
		{
		public:
			FrameBuffer(unsigned int width, unsigned int height);
			~FrameBuffer();

			void Bind() const override;
			void Unbind() const override;

			Ref<Engine::Texture2D> GetTextureAttachment(unsigned int slot) const override;
			Ref<Engine::Texture2D> GetDepthAttachment(unsigned int slot) const override;


			void CreateTextureAttachment() override;
			void CreateRenderBuffer() override;
			void CreateDepthAttachment() override;
		private:
			unsigned int mId;
			unsigned int mRenderBuffer;
			Ref<Engine::Texture2D> mTextureAttachment;
			Ref<Engine::Texture2D> mDepthAttachment;
		};
	}
}
