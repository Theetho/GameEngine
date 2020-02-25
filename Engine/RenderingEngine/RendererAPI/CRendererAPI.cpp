#include "EnginePch.h"
#include "CRendererAPI.h"
#include "COpenGL.h"

#define SELECTED_API COpenGLRenderer

namespace Engine
{
	// Here is defined the rendering API used by the engine
	CAPI CRendererAPI::_sApi = CAPI::OpenGL;
	Ref<CRendererAPI> CRendererAPI::_sInstance = CreateRef<SELECTED_API>();

	CAPI CRendererAPI::_GetAPI()
	{
		return _sApi;
	}

	Ref<CRendererAPI> CRendererAPI::_Get()
	{
		if (!_sInstance)
			_sInstance = CreateRef<SELECTED_API>();

		return _sInstance;
	}

	void CRendererAPI::_SetDrawMode(CDrawMode dm)
	{
		_mDrawMode = dm;
	}
}