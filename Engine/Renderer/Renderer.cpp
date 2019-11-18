#include "EnginePch.h"
#include "Renderer.h"

namespace Engine
{
	Scope<RenderCommand> Renderer::s_renderCommand = std::make_unique<RenderCommand>();

	Renderer::SceneData Renderer::s_sceneData;
	Ref<Shader> Renderer::s_shader;


	void Renderer::BeginScene(
		Camera3D& camera,
		Ref<Shader> shader
	)
	{
		s_sceneData.VP = camera.getVP();

		s_shader = shader;

		s_shader->bind();

		if (s_renderCommand->getAPI() == API::OpenGL)
		{
			auto& openglShader = std::dynamic_pointer_cast<Engine::OpenGLShader>(shader);
			openglShader->uploadUniform("u_cameraPosition", camera.getPosition());
		}
	}

	void Renderer::Submit(
		const Ref<VertexArray> vao,
		const Transform& transform
	)
	{
		if (s_renderCommand->getAPI() == API::OpenGL)
		{
			auto& openglShader = std::dynamic_pointer_cast<Engine::OpenGLShader>(s_shader);

			openglShader->uploadUniform("u_MVP", s_sceneData.VP * transform.getModel());
			openglShader->uploadUniform("u_model", transform.getModel());
		}

		vao->bind();
		s_renderCommand->drawIndexed(vao);
	}

	void Renderer::Submit(
		const Ref<Model> model,
		const Transform& transform
	)
	{
		if (s_renderCommand->getAPI() == API::OpenGL)
		{
			auto& openglShader = std::dynamic_pointer_cast<Engine::OpenGLShader>(s_shader);

			openglShader->uploadUniform("u_MVP", s_sceneData.VP * transform.getModel());
			openglShader->uploadUniform("u_model", transform.getModel());
		}

		for (const Mesh& mesh : *model)
		{
			auto vao = mesh.getVao();
			mesh.loadMaterial(s_shader);
			vao->bind();
			s_renderCommand->drawIndexed(vao);
		}
	}

	void Renderer::Submit(
		const Ref<Model> model,
		const Ref<Collider> collider
	)
	{
		Transform transform;
		transform.setPosition(collider->getCenter());
		transform.setScale(collider->getMax() - collider->getMin());

		if (s_renderCommand->getAPI() == API::OpenGL)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		 
			auto& openglShader = std::dynamic_pointer_cast<Engine::OpenGLShader>(s_shader);

			openglShader->uploadUniform("u_MVP", s_sceneData.VP * transform.getModel());
		}

		for (const Mesh& mesh : *model)
		{
			auto vao = mesh.getVao();
			vao->bind();
			s_renderCommand->drawIndexed(vao);
		}
		
		if (s_renderCommand->getAPI() == API::OpenGL)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	void Renderer::EndScene()
	{
		s_shader->unbind();
	}
}
