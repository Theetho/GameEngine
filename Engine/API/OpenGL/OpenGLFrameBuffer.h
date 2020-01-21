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
	private:
		unsigned int mId, mWidth, mHeight;
		unsigned int mRenderBuffer;
		Ref<Texture2D> mTextureAttachment;

		void CreateTextureAttachment(unsigned int width, unsigned int height);
		void CreateRenderBuffer(unsigned int width, unsigned int height);
	};
}
