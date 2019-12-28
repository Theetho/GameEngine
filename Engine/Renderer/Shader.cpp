#include "EnginePch.h"
#include "Shader.h"
#include "Rendering/Renderer.h"
#include "Core/Log.h"
#include "API/OpenGL/OpenGLShader.h"

namespace Engine
{
	std::string Shader::sFolderPath = "";

	Shader::Shader(const std::string& file_path, const std::string& name, bool use_folder_path
	)
		: mName(name)
	{}

	Shader::~Shader()
	{}

	Ref<Shader> Shader::Create(const std::string& file_path, const std::string& name, bool use_folder_path)
	{
		ENGINE_ASSERT(sFolderSrc != "", "No folder for the shader files");
		switch (Renderer::GetAPI())
		{
		case Engine::API::None:
			ENGINE_ASSERT(false, "Api not supported");
		case Engine::API::OpenGL:
			return std::make_shared<OpenGLShader>(file_path, name, use_folder_path);
		}

		return nullptr;
	}
	
	const std::string& Shader::GetName() const
	{
		return mName;
	}

	void Shader::SetFolder(const std::string& folder_path)
	{
		sFolderPath = folder_path;
	}
	
	void Shader::SetName(const std::string& name)
	{
		mName = name;
	}
}