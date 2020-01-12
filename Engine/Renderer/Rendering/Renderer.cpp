#include "EnginePch.h"
#include "Renderer/Rendering.h"
#include "Core/Camera3D.h"
#include "API/OpenGL/OpenGLShader.h"


namespace Engine
{
	Ref<RenderCommand> Renderer::sRenderCommand = CreateRef<RenderCommand>();

	Renderer::SceneData Renderer::sSceneData;
	Ref<Shader> Renderer::sShader;

	std::unordered_map<Ref<Shader>, std::vector<const Renderable*>> Renderer::sBatch;

	API Renderer::GetAPI()
	{
		return sRenderCommand->GetAPI();
	}

	void Renderer::SetViewport(unsigned int width, unsigned int height)
	{
		sRenderCommand->SetViewport(width, height);
	}

	void Renderer::Submit(Ref<Shader> shader, const Renderable& renderable)
	{
		sBatch[shader].push_back(&renderable);
	}

	void Renderer::BeginScene(Camera3D& camera)
	{
		sSceneData.view			   = &camera.GetView();
		sSceneData.projection	   = &camera.GetProjection();
		sSceneData.camera_position = &camera.GetPosition();
		sSceneData.view_projection = &camera.GetViewProjection();
	}

	void Renderer::PrepareShader(Ref<Shader> shader)
	{
		shader->Bind();

		if (sRenderCommand->GetAPI() == API::OpenGL)
		{
			auto& open_gl_shader = std::dynamic_pointer_cast<Engine::OpenGLShader>(shader);
			open_gl_shader->UploadUniform("u_cameraPosition", (*sSceneData.camera_position));
			open_gl_shader->UploadUniform("u_view_projection", (*sSceneData.view_projection));
		}
	}

	void Renderer::Render()
	{
		for (auto iterator : sBatch)
		{
			sShader = iterator.first;
			PrepareShader(sShader);

			for (auto renderable : iterator.second)
			{
				renderable->Render(sRenderCommand, sShader);
			}
		}
	}

	void Renderer::EndScene()
	{
		sBatch.clear();
	}
}
