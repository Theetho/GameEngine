#include "EnginePch.h"
#include "Texture.h"

namespace Engine
{

	Texture::Texture(const std::string& file_path)
		: mPath(file_path)
	{}
	
	Texture::~Texture()
	{}

	Texture::Texture()
		: mPath("Path not defined")
	{}
}