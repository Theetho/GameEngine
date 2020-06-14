#include "EnginePch.h"
#include "Renderer/Rendering.h"
#include "API/OpenGL/Shader.h"
#include "Terrain/Water.h"
#include "Core/Camera.h"

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

	void Renderer::BeginScene(Camera3D& camera)
	{
		sSceneData.view = camera.GetViewMatrix();
		sSceneData.projection = camera.GetProjectionMatrix();
		sSceneData.camera_position = camera.GetTransform().GetPosition();
		sSceneData.view_projection = sSceneData.projection * sSceneData.view;
	}

	void Renderer::Submit(Ref<Shader> shader, const Renderable& renderable)
	{
		sBatch[shader].push_back(&renderable);
	}

	void Renderer::PrepareWater(Camera3D& camera, Water& water, Ref<FrameBuffer> binded_framebuffer)
	{
		water.Prepare(camera, binded_framebuffer);
	}

	void Renderer::PrepareShader(Ref<Shader> shader, bool clip)
	{
		shader->Bind();

		if (sRenderCommand->GetAPI() == API::OpenGL)
		{
			auto& open_gl_shader = std::dynamic_pointer_cast<Engine::OpenGL::Shader>(shader);
			open_gl_shader->UploadUniform("uCameraPosition", (sSceneData.camera_position));
			open_gl_shader->UploadUniform("uViewProjection", (sSceneData.view_projection));
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
		sSceneData.cliping_plane = Vec4();
	}
}
