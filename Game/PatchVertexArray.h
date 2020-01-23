#pragma once

class PatchVertexArray : public Engine::OpenGLVertexArray
{
public:
	PatchVertexArray();
	~PatchVertexArray();

	void AddVertexBuffer(Engine::Ref<Engine::VertexBuffer> vertex_buffer) override;
	void AddIndexBuffer(Engine::Ref<Engine::IndexBuffer> index_buffer) override;

private:
	void Render(Engine::Ref<Engine::RenderCommand> render_command, Engine::Ref<Engine::Shader> shader) const override;
};

