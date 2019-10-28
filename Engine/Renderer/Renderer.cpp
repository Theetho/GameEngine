#include "EnginePch.h"
#include "Renderer.h"

namespace Engine
{
	RenderCommand* Renderer::s_renderCommand = new RenderCommand();
	Renderer::SceneData Renderer::s_sceneData;

	void Renderer::beginScene(
		Camera3D& camera
	)
	{
		s_sceneData.VP = camera.getVP();
	}

	void Renderer::submit(
		const std::shared_ptr<Shader>& shader,
		const std::shared_ptr<VertexArray>& vao
	)
	{
		shader->bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniform("u_VP", s_sceneData.VP);
		vao->bind();
		s_renderCommand->drawIndexed(vao);
	}

	void Renderer::endScene()
	{
	}
}
