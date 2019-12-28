#include "EnginePch.h"
#include "Texture.h"
#include <filesystem>

namespace Engine
{
	std::string Texture::sFolder = "";

	Texture::Texture(const std::string& file_path, const std::string& name, bool use_folder_path)
		: mName(name)
		, mWidth(0)
		, mHeight(0)
	{
		// Setting the name of the texture
		if (mName == "")
		{
			auto last_slash = file_path.find_last_of("/\\");
			last_slash = last_slash == std::string::npos ? 0 : last_slash + 1;
			auto last_dot = file_path.rfind('.');
			int count = last_dot == std::string::npos ? file_path.size() - last_slash : last_dot - last_slash;

			mName = file_path.substr(last_slash, count);
		}
	}
	
	Texture::~Texture()
	{}
	
	unsigned int Texture::GetWidth() const
	{
		return mWidth;
	}
	
	unsigned int Texture::GetHeight() const
	{
		return mHeight;
	}

	const std::string& Texture::GetName() const
	{
		return mName;
	}
	
	void Texture::SetFolder(const std::string& folder)
	{
		sFolder = folder;
	}
	
	void Texture::SetName(const std::string& name)
	{
		mName = name;
	}
}