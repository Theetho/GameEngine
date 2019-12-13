#include "EnginePch.h"
#include "Texture2D.h"
#include <filesystem>
#include "../Rendering/Renderer.h"
#include "API/OpenGL/OpenGLTexture2D.h"

namespace Engine
{
	Texture2D::Texture2D(
		const std::string& filePath,
		const std::string& name,
		const bool& useFolderPath
	)
		: Texture(filePath, name, useFolderPath)
	{
	}

	Ref<Texture2D> Texture2D::Create(
		const std::string& filePath,
		const std::string& name,
		const bool& useFolderPath
	)
	{
		switch (Renderer::getAPI())
		{
		case Engine::API::None:
			ENGINE_ASSERT(false, "Api not supported");
		case Engine::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(filePath, name, useFolderPath);
		}
	}
}