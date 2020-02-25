#include "EnginePch.h"
#include "CRenderingPipeline.h"
#include "Renderable/CRenderable.h"
#include "RendererAPI/CRendererAPI.h"
#include "Renderer/CRenderer.h"

#define IF_HAS_BEEN_INITIALIZED if(!_sHasBeenInitialized) ENGINE_LOG_ERROR("RendererPipeline must be initialized !"); return

namespace Engine
{
	bool RenderingPipeline::_sHasBeenInitialized = false;

	void RenderingPipeline::_Initialize()
	{
		sInstance->_mRenderer2D._Initialize();
		sInstance->_mRenderer3D._Initialize();

		_sHasBeenInitialized = true;
	}

	void RenderingPipeline::_Clear()
	{
		CRendererAPI::_Get()->_Clear();
	}

	void RenderingPipeline::_Clear(const Color& color)
	{
		CRendererAPI::_Get()->_SetClearColor(color);
		CRendererAPI::_Get()->_Clear();
	}

	void RenderingPipeline::_BeginScene(Camera* camera)
	{
		IF_HAS_BEEN_INITIALIZED;
		sInstance->_mRenderer2D._BeginScene(camera);
		sInstance->_mRenderer3D._BeginScene(camera);
	}

	void RenderingPipeline::_Submit(CRenderable2D* renderable2D)
	{
		IF_HAS_BEEN_INITIALIZED;
		// Renderable2D stuff
		sInstance->_mRenderer2D._Submit(renderable2D);
	}

	void RenderingPipeline::_Submit(CRenderable3D* renderable3D)
	{
		IF_HAS_BEEN_INITIALIZED;
		// Renderable3D stuff
		sInstance->_mRenderer3D._Submit(renderable3D);
	}

	void RenderingPipeline::_Render()
	{
		IF_HAS_BEEN_INITIALIZED;
		// 3D stuff first
		sInstance->_mRenderer3D._Render();
		sInstance->_mRenderer2D._Render();
	}

	void RenderingPipeline::_EndScene()
	{
		IF_HAS_BEEN_INITIALIZED;
		sInstance->_mRenderer2D._EndScene();
		sInstance->_mRenderer3D._EndScene();
	}
}