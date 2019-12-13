#include "EnginePch.h"
#include "OpenGLCubeMap.h"
#include <filesystem>
#include "Core/Log.h"

namespace Engine
{
	OpenGLCubeMap::OpenGLCubeMap(
		const std::string& folderPath,
		const std::string& name,
		const bool& useFolderPath
	)
		: CubeMap(folderPath, name, useFolderPath)
	{
		int i = 0;

		stbi_set_flip_vertically_on_load(false);
		
		std::string skyboxesPath =
		useFolderPath
		?
		s_folder + folderPath
		:
		folderPath;

		glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &m_id);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);

		for (const auto& texture : std::filesystem::directory_iterator(skyboxesPath))
		{

			int w, h, c;

			stbi_uc* data = stbi_load(texture.path().string().c_str(), &w, &h, &c, 0);

			if (!data)
			{
				data = stbi_load("../Engine/Assets/Textures/error.png", &w, &h, &c, 0);
				ENGINE_LOG_WARN("Failed to load the texture : {0}", texture.path().string());
			}


			GLenum internalFormat = 0, dataFormat = 0;
			if (c == 4)
			{
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
			}
			else if (c == 3)
			{
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
			}

			ENGINE_ASSERT(internalFormat & dataFormat, "Format not supported!");

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalFormat,
				w, h, 0, dataFormat, GL_UNSIGNED_BYTE, data);

			++i;
			stbi_image_free(data);
		}
		
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	OpenGLCubeMap::~OpenGLCubeMap()
	{
	}
}