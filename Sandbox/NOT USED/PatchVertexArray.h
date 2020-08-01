#pragma once

class PatchVertexArray : public Engine::OpenGL::VertexArray
{
public:
	PatchVertexArray();
	~PatchVertexArray();

	void AddPatch(const std::vector<float>& vertices, unsigned int patch_size);
private:
	unsigned int mVbo, mSize;
	void Render(Engine::Ref<Engine::RenderCommand> render_command, Engine::Ref<Engine::Shader> shader) const override;
};

