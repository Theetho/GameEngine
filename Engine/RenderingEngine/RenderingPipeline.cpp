#include "EnginePch.h"
#include "RenderingPipeline.h"
#include "Renderable/Renderable.h"
#include "RendererAPI/RendererAPI.h"
#include "Renderer/Renderer.h"

namespace Engine
{
	void RenderingPipeline::BeginScene(Camera* camera)
	{
		sInstance->mRenderer2D.BeginScene(camera);
		sInstance->mRenderer3D.BeginScene(camera);
	}

	void RenderingPipeline::Submit(CRenderable2D* renderable2D)
	{
		// Renderable2D stuff
		sInstance->mRenderer2D.Submit(renderable2D);
	}

	void RenderingPipeline::Submit(CRenderable3D* renderable3D)
	{
		// Renderable3D stuff
		sInstance->mRenderer3D.Submit(renderable3D);
	}

	void RenderingPipeline::Render()
	{
		// 3D stuff first
		sInstance->mRenderer3D.Render();
		sInstance->mRenderer2D.Render();
	}

	void RenderingPipeline::EndScene()
	{
		sInstance->mRenderer2D.EndScene();
		sInstance->mRenderer3D.EndScene();
	}
}