#include "EnginePch.h"
#include "FrameBuffer.h"
#include "API/OpenGL/OpenGLFrameBuffer.h"
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
				return CreateRef<OpenGLFrameBuffer>(width, height);
		}

		return nullptr;
	}
}