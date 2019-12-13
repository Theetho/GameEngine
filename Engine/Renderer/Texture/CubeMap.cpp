#include "EnginePch.h"
#include "CubeMap.h"
#include <filesystem>
#include "Renderer/Rendering/Renderer.h"
#include "API/OpenGL/OpenGLCubeMap.h"

namespace Engine
{
	CubeMap::CubeMap(
		const std::string& folderPath,
		const std::string& name,
		const bool& useFolderPath
	)
		: Texture(folderPath, name, useFolderPath)
	{
	}

	CubeMap::~CubeMap()
	{
	}

	Ref<CubeMap> CubeMap::Create(const std::string& filePath, const std::string& name, const bool& useFolderPath)
	{
		switch (Renderer::getAPI())
		{
		case Engine::API::None:
			ENGINE_ASSERT(false, "Api not supported");
		case Engine::API::OpenGL:
			return std::make_shared<OpenGLCubeMap>(filePath, name, useFolderPath);
		}
	}
}