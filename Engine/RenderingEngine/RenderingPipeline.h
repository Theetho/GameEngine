#pragma once

#include "Util/Singleton.h"
#include "./Renderer/Renderer.h"
#include "./Renderable/Renderable.h"

namespace Engine
{
	using Camera = Camera3D;

	// Interface between renderers and engine
	class RenderingPipeline : public Singleton<RenderingPipeline>
	{
	public:
		static void BeginScene(Camera* camera);
		static void Submit(CRenderable2D* renderable);
		static void Submit(CRenderable3D* renderable);
		static void Render();
		static void EndScene();
	private:
		CRenderer2D mRenderer2D;
		CRenderer3D mRenderer3D;
	};
}

