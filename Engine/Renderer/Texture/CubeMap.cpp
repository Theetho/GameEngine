#include "EnginePch.h"
#include "CubeMap.h"
#include <filesystem>
#include "Renderer/Rendering/Renderer.h"
#include "Renderer/Rendering/RendererAPI.h"
#include "API/OpenGL/OpenGLCubeMap.h"

namespace Engine
{
	CubeMap::CubeMap(const std::string& folderPath, const std::string& name, bool use_folder_path)
		: Texture(folderPath, name, use_folder_path)
	{}

	CubeMap::~CubeMap()
	{}

	Ref<CubeMap> CubeMap::Create(const std::string& file_path, const std::string& name, bool use_folder_path)
	{
		switch (Renderer::GetAPI())
		{
		case Engine::API::None:
			ENGINE_ASSERT(false, "Api not supported");
		case Engine::API::OpenGL:
			return CreateRef<OpenGLCubeMap>(file_path, name, use_folder_path);
		}
	}
}