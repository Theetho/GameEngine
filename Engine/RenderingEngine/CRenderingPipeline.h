#pragma once

#include "Util/Singleton.h"
#include "Renderer/CRenderer.h"
#include "Renderable/CRenderable.h"

namespace Engine
{
	using Camera = Camera3D;

	// Interface between renderers and engine
	class RenderingPipeline : public Engine::Singleton<RenderingPipeline>
	{
	public:
		static void _Initialize();
		static void _Clear();
		static void _Clear(const Color& color);
		static void _BeginScene(Camera* camera);
		static void _Submit(CRenderable2D* renderable);
		static void _Submit(CRenderable3D* renderable);
		static void _Render();
		static void _EndScene();
	private:
		static bool _sHasBeenInitialized;
		CRenderer2D _mRenderer2D;
		CRenderer3D _mRenderer3D;
	};
}

