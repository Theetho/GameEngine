#include "EnginePch.h"
#include "FrameBuffer.h"
#include "Shader.h"
#include "Core/Application.h"
#include "Core/Window.h"
#include "Texture2D.h"

namespace Engine
{
	namespace OpenGL
	{
		FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
			: Engine::FrameBuffer(width, height)
			, mTextureAttachment(0)
			, mRenderBuffer(0)
		{
			glGenFramebuffers(1, &mId);

			glBindFramebuffer(GL_FRAMEBUFFER, mId);
			glDrawBuffer(GL_COLOR_ATTACHMENT0);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		FrameBuffer::~FrameBuffer()
		{
			glDeleteRenderbuffers(1, &mRenderBuffer);

			glDeleteFramebuffers(1, &mId);
		}

		void FrameBuffer::Bind() const
		{
			glBindFramebuffer(GL_FRAMEBUFFER, mId);
			glViewport(0, 0, mWidth, mHeight);
		}

		void FrameBuffer::Unbind(Ref<Engine::FrameBuffer> binded_framebuffer) const
		{
			if (binded_framebuffer)
			{
				binded_framebuffer->Bind();
			}
			else
			{
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				glViewport(0, 0, Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());
			}
		}

		Ref<Engine::Texture2D> FrameBuffer::GetTextureAttachment(unsigned int slot) const
		{
			return mTextureAttachment;
		}

		Ref<Engine::Texture2D> FrameBuffer::GetDepthAttachment(unsigned int slot) const
		{
			return mDepthAttachment;
		}

		void FrameBuffer::CreateDepthAttachment()
		{
			this->Bind();

			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, mWidth, mHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);

			mDepthAttachment = CreateRef<Texture2D>(mWidth, mHeight, texture);

			this->Unbind();
		}

		void FrameBuffer::CreateTextureAttachment()
		{
			this->Bind();

			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

			mTextureAttachment = CreateRef<Texture2D>(mWidth, mHeight, texture);

			this->Unbind();
		}

		void FrameBuffer::CreateRenderBuffer()
		{
			this->Bind();

			glGenRenderbuffers(1, &mRenderBuffer);

			glBindRenderbuffer(GL_RENDERBUFFER, mRenderBuffer);

			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, mWidth, mHeight);

			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mRenderBuffer);

			this->Unbind();
		}
	}
}