#include "EnginePch.h"
#include "VertexBuffer.h"
#include "BufferLayout.h"
#include "Renderer/Rendering/Renderer.h"
#include "API/OpenGL/OpenGLVertexBuffer.h"

namespace Engine
{
	VertexBuffer::~VertexBuffer()
	{}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, unsigned int size)
	{
		switch (Renderer::GetAPI())
		{
		case Engine::API::None:
			ENGINE_ASSERT(false, "Api not supported");
		case Engine::API::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}
	}
}