#include "EnginePch.h"
#include "OpenGLFrameBuffer.h"
#include "OpenGLShader.h"
#include "Core/Application.h"
#include "Core/Window.h"
#include "API/OpenGL/OpenGLTexture2D.h"

namespace Engine
{
	OpenGLFrameBuffer::OpenGLFrameBuffer(unsigned int width, unsigned int height)
		: mId(0)
		, mWidth(width)
		, mHeight(height)
		, mTextureAttachment(0)
		, mRenderBuffer(0)
	{
		glGenFramebuffers(1, &mId);

		glBindFramebuffer(GL_FRAMEBUFFER, mId);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);

		this->CreateTextureAttachment(width, height);
		this->CreateRenderBuffer(width, height);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteRenderbuffers(1, &mRenderBuffer);
	
		glDeleteFramebuffers(1, &mId);
	}
	
	void OpenGLFrameBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, mId);
		glViewport(0, 0, mWidth, mHeight);
	}
	
	void OpenGLFrameBuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());
	}

	Ref<Texture2D> OpenGLFrameBuffer::GetTextureAttachment(unsigned int slot) const
	{
		return mTextureAttachment;
	}

	Ref<Texture2D> OpenGLFrameBuffer::GetDepthAttachment(unsigned int slot) const
	{
		return mDepthAttachment;
	}

	Ref<Texture2D> OpenGLFrameBuffer::CreateDepthAttachment()
	{
		this->Bind();

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, mWidth, mHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);

		mDepthAttachment = CreateRef<OpenGLTexture2D>(mWidth, mHeight, texture);

		this->Unbind();

		return mDepthAttachment;
	}

	void OpenGLFrameBuffer::CreateTextureAttachment(unsigned int width, unsigned int height)
	{
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

		mTextureAttachment = CreateRef<OpenGLTexture2D>(width, height, texture);
	}
	
	void OpenGLFrameBuffer::CreateRenderBuffer(unsigned int width, unsigned int height)
	{
		glGenRenderbuffers(1, &mRenderBuffer);
		
		glBindRenderbuffer(GL_RENDERBUFFER, mRenderBuffer);
		
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mRenderBuffer);
	}
}