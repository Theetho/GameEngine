#include "EnginePch.h"
#include "RendererAPI.h"
#include "OpenGL.h"

namespace Engine
{
	// Here is defined the rendering API used by the engine
	API CRendererAPI::sApi = API::OpenGL;
	Ref<CRendererAPI> CRendererAPI::sInstance = CreateRef<OpenGL::Renderer>();

	API CRendererAPI::GetAPI()
	{
		return sApi;
	}

	Ref<CRendererAPI> CRendererAPI::Get()
	{
		return sInstance;
	}

	void CRendererAPI::SetDrawMode(DrawMode dm)
	{
		mDrawMode = dm;
	}
}