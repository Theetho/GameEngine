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
		const Ref<Shader>& shader,
		const Ref<VertexArray>& vao,
		const Transform& transform
	)
	{
		shader->bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniform(
			"u_MVP",
			s_sceneData.VP * transform.getModel()
		);
		vao->bind();
		s_renderCommand->drawIndexed(vao);
	}

	void Renderer::endScene()
	{
	}
}
