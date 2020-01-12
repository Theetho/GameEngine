#include "EnginePch.h"
#include "VertexArray.h"
#include "Renderer/Rendering.h"
#include "API/OpenGL/OpenGLVertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

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
			return CreateRef<OpenGLVertexArray>();
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

	void VertexArray::Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const
	{
		Bind();
		render_command->DrawIndexed(*this);
	}
}