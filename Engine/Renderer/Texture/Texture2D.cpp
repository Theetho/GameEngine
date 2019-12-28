#include "EnginePch.h"
#include "Texture2D.h"
#include <filesystem>
#include "../Rendering/Renderer.h"
#include "API/OpenGL/OpenGLTexture2D.h"

namespace Engine
{
	Texture2D::Texture2D(const std::string& file_path, const std::string& name, bool use_folder_path)
		: Texture(file_path, name, use_folder_path)
	{}

	Texture2D::~Texture2D()
	{}

	Ref<Texture2D> Texture2D::Create(const std::string& file_path, const std::string& name, bool use_folder_path)
	{
		switch (Renderer::GetAPI())
		{
		case Engine::API::None:
			ENGINE_ASSERT(false, "Api not supported");
		case Engine::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(file_path, name, use_folder_path);
		}
	}
}