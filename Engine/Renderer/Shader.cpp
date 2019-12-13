#include "EnginePch.h"
#include "Shader.h"
#include "Rendering/Renderer.h"
#include "Core/Log.h"
#include "API/OpenGL/OpenGLShader.h"

namespace Engine
{
	std::string Shader::s_folderPath = "";

	Shader::Shader(
		const std::string& filePath,
		const std::string& name,
		const bool& useFolderPath
	)
		: m_name(name)
	{
	}

	Ref<Shader> Shader::Create(
		const std::string& filePath,
		const std::string& name,
		const bool& useFolderPath
	)
	{
		ENGINE_ASSERT(s_folderSrc != "", "No folder for the shader files");
		switch (Renderer::getAPI())
		{
		case Engine::API::None:
			ENGINE_ASSERT(false, "Api not supported");
		case Engine::API::OpenGL:
			return std::make_shared<OpenGLShader>(filePath, name, useFolderPath);
		}

		return nullptr;
	}
}