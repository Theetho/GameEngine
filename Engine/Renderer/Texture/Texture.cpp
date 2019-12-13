#include "EnginePch.h"
#include "Texture.h"
#include <filesystem>

namespace Engine
{
	std::string Texture::s_folder = "";

	Texture::Texture(
		const std::string& filePath,
		const std::string& name,
		const bool& useFolderPath
	)
		: m_name(name)
		, m_width(0)
		, m_height(0)
	{
		// Setting the name of the texture
		if (m_name == "")
		{
			auto lastSlash = filePath.find_last_of("/\\");
			lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
			auto lastDot = filePath.rfind('.');
			int count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;

			m_name = filePath.substr(lastSlash, count);
		}
	}
}