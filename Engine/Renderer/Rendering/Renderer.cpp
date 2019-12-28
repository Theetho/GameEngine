#include "EnginePch.h"
#include "Renderer.h"

namespace Engine
{
	Scope<RenderCommand> Renderer::sRenderCommand = std::make_unique<RenderCommand>();

	Renderer::SceneData Renderer::sSceneData;
	Ref<Shader> Renderer::sShader;

	API Renderer::GetAPI()
	{
		return sRenderCommand->GetAPI();
	}

	void Renderer::SetViewport(unsigned int width, unsigned int height)
	{
		sRenderCommand->SetViewport(width, height);
	}

	void Renderer::BeginScene(Camera3D& camera, Ref<Shader> shader)
	{
		sSceneData.ViewProjection = camera.GetViewProjection();
		sSceneData.View           = camera.GetView();
		sSceneData.Projection     = camera.GetProjection();

		sShader = shader;

		sShader->Bind();

		if (sRenderCommand->GetAPI() == API::OpenGL)
		{
			auto& open_gl_shader = std::dynamic_pointer_cast<Engine::OpenGLShader>(shader);
			open_gl_shader->UploadUniform("u_cameraPosition", camera.GetPosition());
		}
	}

	void Renderer::Submit(Ref<VertexArray> vertex_array, const Transform& transform)
	{
		if (sRenderCommand->GetAPI() == API::OpenGL)
		{
			auto& open_gl_shader = std::dynamic_pointer_cast<Engine::OpenGLShader>(sShader);

			open_gl_shader->UploadUniform("u_ModelViewProjection", sSceneData.ViewProjection * transform.GetModel());
			open_gl_shader->UploadUniform("u_model", transform.GetModel());
		}

		vertex_array->Bind();
		sRenderCommand->DrawIndexed(vertex_array);
	}

	void Renderer::Submit(const Model& model, const Transform& transform)
	{
		if (sRenderCommand->GetAPI() == API::OpenGL)
		{
			auto& open_gl_shader = std::dynamic_pointer_cast<Engine::OpenGLShader>(sShader);

			open_gl_shader->UploadUniform("u_ModelViewProjection", sSceneData.ViewProjection * transform.GetModel());
			open_gl_shader->UploadUniform("u_model", transform.GetModel());
		}

		for (const Mesh& mesh : model)
		{
			auto vertex_array = mesh.GetVao();
			mesh.LoadMaterial(sShader);
			vertex_array->Bind();
			sRenderCommand->DrawIndexed(vertex_array);
		}
	}

	void Renderer::Submit(const Model& model, Ref<Collider> collider)
	{
		Transform transform;
		transform.SetPosition(collider->GetCenter());
		transform.SetScale(collider->GetMax() - collider->GetMin());

		if (sRenderCommand->GetAPI() == API::OpenGL)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		 
			auto& open_gl_shader = std::dynamic_pointer_cast<Engine::OpenGLShader>(sShader);

			open_gl_shader->UploadUniform("u_ModelViewProjection", sSceneData.ViewProjection * transform.GetModel());
		}

		for (const Mesh& mesh : model)
		{
			auto vertex_array = mesh.GetVao();
			vertex_array->Bind();
			sRenderCommand->DrawIndexed(vertex_array);
		}
		
		if (sRenderCommand->GetAPI() == API::OpenGL)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	void Renderer::Submit(const Skybox& skybox)
	{
		if (sRenderCommand->GetAPI() == API::OpenGL)
		{
			glDisable(GL_CULL_FACE);
			glDepthFunc(GL_LEQUAL);

			auto& open_gl_shader = std::dynamic_pointer_cast<Engine::OpenGLShader>(sShader);

			open_gl_shader->UploadUniform("u_ViewProjection", sSceneData.ViewProjection);
		}

		for (auto& mesh : skybox.GetModel()->GetMeshes())
		{
			auto vertex_array = mesh.GetVao();
			vertex_array->Bind();
			sRenderCommand->DrawIndexed(vertex_array);
		}

		if (sRenderCommand->GetAPI() == API::OpenGL)
		{
			glEnable(GL_CULL_FACE);
			glDepthFunc(GL_LESS);
		}
	}

	void Renderer::EndScene()
	{
		sShader->Unbind();
	}
}
