#include "EnginePch.h"
#include "Renderer/Rendering.h"
#include "Core/Camera3D.h"
#include "API/OpenGL/Shader.h"
#include "Terrain/Water.h"


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

	void Renderer::SetDrawMode(DrawMode draw_mode)
	{
		sRenderCommand->SetDrawMode(draw_mode);
	}

	void Renderer::SetViewport(unsigned int width, unsigned int height)
	{
		sRenderCommand->SetViewport(width, height);
	}

	void Renderer::Submit(Ref<Shader> shader, const Renderable& renderable)
	{
		sBatch[shader].push_back(&renderable);
	}

	void Renderer::PrepareWater(Camera3D& camera, Water& water)
	{
		water.Prepare(camera);
	}

	void Renderer::BeginScene(Camera3D& camera)
	{
		sSceneData.view			   = &camera.GetView();
		sSceneData.projection	   = &camera.GetProjection();
		sSceneData.camera_position = &camera.GetPosition();
		sSceneData.view_projection = &camera.GetViewProjection();
	}

	void Renderer::PrepareShader(Ref<Shader> shader, bool clip)
	{
		shader->Bind();

		if (sRenderCommand->GetAPI() == API::OpenGL)
		{
			auto& open_gl_shader = std::dynamic_pointer_cast<Engine::OpenGL::Shader>(shader);
			open_gl_shader->UploadUniform("uCameraPosition", (*sSceneData.camera_position));
			open_gl_shader->UploadUniform("uViewProjection", (*sSceneData.view_projection));
			if (clip)
				open_gl_shader->UploadUniform("uClipingPlane", (sSceneData.cliping_plane));
		}
	}

	void Renderer::Render(bool clip)
	{
		for (auto iterator : sBatch)
		{
			sShader = iterator.first;
			PrepareShader(sShader, clip);

			for (auto renderable : iterator.second)
			{
				renderable->Render(sRenderCommand, sShader);
			}
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
		sSceneData.view			   = nullptr;
		sSceneData.projection	   = nullptr;
		sSceneData.camera_position = nullptr;
		sSceneData.view_projection = nullptr;
		sSceneData.cliping_plane   = Vec4();
	}
}
