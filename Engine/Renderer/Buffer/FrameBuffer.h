#pragma once

namespace Engine
{
	class Texture2D;

	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer();

		static Ref<FrameBuffer> Create(unsigned int width, unsigned int height);

		virtual void Bind() const = 0;
		virtual void Unbind(Ref<FrameBuffer> binded_framebuffer = nullptr) const = 0;
		
		virtual Ref<Texture2D> GetTextureAttachment(unsigned int slot = 0) const = 0;
		virtual Ref<Texture2D> GetDepthAttachment(unsigned int slot = 0) const = 0;
		virtual inline uint GetID()
		{
			return mId;
		}
		
		virtual void CreateTextureAttachment() = 0;
		virtual void CreateRenderBuffer() = 0;
		virtual void CreateDepthAttachment() = 0;

	protected:
		uint mWidth, mHeight, mId;

		FrameBuffer(unsigned int width, unsigned int height);
	};
}

