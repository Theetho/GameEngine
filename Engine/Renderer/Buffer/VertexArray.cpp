#include "EnginePch.h"
#include "VertexArray.h"
#include "Renderer/Rendering.h"
#include "API/OpenGL/VertexArray.h"
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
			return CreateRef<OpenGL::VertexArray>();
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

	bool VertexArray::IsIndexed() const
	{
		return (bool)mIndexBuffer;
	}

	void VertexArray::Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const
	{
		Bind();
		render_command->Draw(*this);
	}
}