#include "EnginePch.h"
#include "Shader.h"
#include "Rendering/Renderer.h"
#include "Rendering/RendererAPI.h"
#include "API/OpenGL/Shader.h"

namespace Engine
{
	Shader::Shader(const std::string& file_path)
	{}

	Shader::~Shader()
	{}

	Ref<Shader> Shader::Create(const std::string& file_path)
	{
		ENGINE_ASSERT(sFolderSrc != "", "No folder for the shader files");
		switch (Renderer::GetAPI())
		{
			case Engine::API::None:
				ENGINE_ASSERT(false, "Api not supported");
			case Engine::API::OpenGL:
				return CreateRef<OpenGL::Shader>(file_path);
		}

		return nullptr;
	}
}