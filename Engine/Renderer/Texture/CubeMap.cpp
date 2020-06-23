#include "EnginePch.h"
#include "CubeMap.h"
#include <filesystem>
#include "Renderer/Rendering/Renderer.h"
#include "Renderer/Rendering/RendererAPI.h"
#include "API/OpenGL/CubeMap.h"

namespace Engine
{
	CubeMap::CubeMap(const std::string& folder_path)
		: Texture(folder_path)
	{}

	CubeMap::~CubeMap()
	{}

	Ref<CubeMap> CubeMap::Create(const std::string& file_path)
	{
		switch (Renderer::GetAPI())
		{
		case Engine::API::None:
			ENGINE_ASSERT(false, "Api not supported");
		case Engine::API::OpenGL:
			return CreateRef<OpenGL::CubeMap>(file_path);
		}
	}
}