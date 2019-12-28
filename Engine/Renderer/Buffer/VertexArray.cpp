#include "EnginePch.h"
#include "VertexArray.h"
#include "Renderer/Rendering/Renderer.h"
#include "API/OpenGL/OpenGLVertexArray.h"

namespace Engine
{
	VertexArray::~VertexArray()
	{}

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case Engine::API::None:
			ENGINE_ASSERT(false, "Api not supported");
		case Engine::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		}

		return nullptr;
	}
	
	const std::vector<Ref<VertexBuffer>>& VertexArray::GetVertexBuffers() const
	{
		return mVertexBuffers;
	}
	
	const Ref<IndexBuffer> VertexArray::GetIndexBuffer() const
	{
		return mIndexBuffer;
	}
}