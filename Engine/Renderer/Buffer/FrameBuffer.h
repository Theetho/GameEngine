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
		virtual void Unbind() const = 0;
		
		virtual Ref<Texture2D> GetTextureAttachment(unsigned int slot = 0) const = 0;
		virtual Ref<Texture2D> GetDepthAttachment(unsigned int slot = 0) const = 0;
		
		virtual void CreateTextureAttachment() = 0;
		virtual void CreateRenderBuffer() = 0;
		virtual void CreateDepthAttachment() = 0;
	};
}

