#include "EnginePch.h"
#include "FrameBuffer.h"
#include "API/OpenGL/FrameBuffer.h"
#include "Renderer/Rendering/Renderer.h"
#include "Renderer/Rendering/RendererAPI.h"

namespace Engine
{
	FrameBuffer::~FrameBuffer()
	{}

	Ref<FrameBuffer> FrameBuffer::Create(unsigned int width, unsigned int height)
	{
		switch (Renderer::GetAPI())
		{
			case API::None:
				ENGINE_ASSERT(false, "Api not supported");
			case API::OpenGL:
				return CreateRef<OpenGL::FrameBuffer>(width, height);
		}

		return nullptr;
	}

	FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
		: mWidth(width)
		, mHeight(height)
	{}
}