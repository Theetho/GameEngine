#pragma once

#include "Renderer/Buffer/FrameBuffer.h"

namespace Engine
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(unsigned int width, unsigned int height);
		~OpenGLFrameBuffer();

		void Bind() const override;
		void Unbind() const override;
	
		Ref<Texture2D> GetTextureAttachment(unsigned int slot) const override;
		Ref<Texture2D> GetDepthAttachment(unsigned int slot) const override;
	

		void CreateTextureAttachment() override;
		void CreateRenderBuffer() override;
		void CreateDepthAttachment() override;
	private:
		unsigned int mId, mWidth, mHeight;
		unsigned int mRenderBuffer;
		Ref<Texture2D> mTextureAttachment;
		Ref<Texture2D> mDepthAttachment;
	};
}
