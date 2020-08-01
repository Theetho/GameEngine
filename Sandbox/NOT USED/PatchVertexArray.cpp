#include "pch.h"
#include "PatchVertexArray.h"

using namespace Engine;

PatchVertexArray::PatchVertexArray()
	: OpenGL::VertexArray()
	, mSize(0)
{
	glGenBuffers(1, &mVbo);
}

PatchVertexArray::~PatchVertexArray()
{
	glDeleteBuffers(1, &mVbo);
}

void PatchVertexArray::AddPatch(const std::vector<float>& vertices, unsigned int patch_size)
{
	mSize = vertices.size();

	glBindVertexArray(mId);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 2, 0);
	glPatchParameteri(GL_PATCH_VERTICES, patch_size);

	glBindVertexArray(0);
}

void PatchVertexArray::Render(Engine::Ref<Engine::RenderCommand> render_command, Engine::Ref<Engine::Shader> shader) const
{
	glBindVertexArray(mId);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_PATCHES, 0, mSize);
}
