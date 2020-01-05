#include "EnginePch.h"
#include "Texture.h"

namespace Engine
{
	std::string Texture::sFolder = "";

	Texture::Texture(const std::string& file_path, const std::string& name, bool use_folder_path)
		: mName(name)
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