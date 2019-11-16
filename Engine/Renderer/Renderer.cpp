#include "EnginePch.h"
#include "Renderer.h"

namespace Engine
{
	RenderCommand* Renderer::s_renderCommand = new RenderCommand();

	Renderer::SceneData Renderer::s_sceneData;

	void Renderer::BeginScene(
		Camera3D& camera
	)
	{
		s_sceneData.VP = camera.getVP();
	}

	void Renderer::Submit(
		const Ref<Shader>& shader,
		const Ref<VertexArray>& vao,
		const Transform& transform
	)
	{
		shader->bind();

		if (s_renderCommand->getAPI() == API::OpenGL)
		{
			std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniform(
				"u_MVP",
				s_sceneData.VP * transform.getModel()
			);
			std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniform(
				"u_model",
				transform.getModel()
			);
		}

		vao->bind();
		s_renderCommand->drawIndexed(vao);
	}

	void Renderer::Submit(
		const Ref<Shader>& shader,
		const Ref<Model>& model,
		const Transform& transform
	)
	{
		shader->bind();

		if (s_renderCommand->getAPI() == API::OpenGL)
		{
			std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniform(
				"u_MVP",
				s_sceneData.VP * transform.getModel()
			);
			std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniform(
				"u_model",
				transform.getModel()
			);
		}

		for (const Mesh& mesh : *model)
		{
			auto vao = mesh.getVao();
			mesh.bindTextures();
			vao->bind();
			s_renderCommand->drawIndexed(vao);
		}
	}

	void Renderer::EndScene()
	{
	}
}
