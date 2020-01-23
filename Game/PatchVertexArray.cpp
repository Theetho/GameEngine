#include "pch.h"
#include "PatchVertexArray.h"

using namespace Engine;

PatchVertexArray::PatchVertexArray()
	: OpenGLVertexArray()
{
}

PatchVertexArray::~PatchVertexArray()
{}

void PatchVertexArray::AddVertexBuffer(Engine::Ref<Engine::VertexBuffer> vertex_buffer)
{
	glBindVertexArray(mId);
	vertex_buffer->Bind();

	ENGINE_ASSERT(vertex_buffer->GetLayout().GetElements().size(), "Vbo has no layout");

	unsigned int index = 0;

	const auto& layout = vertex_buffer->GetLayout();

	for (const auto& element : layout)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(
			index++,
			element.GetElementCount(),
			ShaderDataTypeToGLType(element.type),
			element.normalized ? GL_TRUE : GL_FALSE,
			layout.GetStride(),
			(const void*)element.offset
		);
	}

	glPatchParameteri(GL_PATCH_VERTICES, vertex_buffer->GetCount());

	mVertexBuffers.push_back(vertex_buffer);
}

// Override on purpose
void PatchVertexArray::AddIndexBuffer(Engine::Ref<Engine::IndexBuffer> index_buffer)
{}

void PatchVertexArray::Render(Engine::Ref<Engine::RenderCommand> render_command, Engine::Ref<Engine::Shader> shader) const
{
	Renderer::SetDrawMode(DrawMode::PATCHES);
	VertexArray::Render(render_command, shader);
	Renderer::SetDrawMode(DrawMode::DEFAULT);
}
