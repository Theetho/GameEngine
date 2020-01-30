#include "EnginePch.h"
#include "CubeMap.h"
#include <filesystem>

namespace Engine
{
	namespace OpenGL
	{
		CubeMap::CubeMap(const std::string& folder_path, const std::string& name, bool use_folder_path)
			: Engine::CubeMap(folder_path, name, use_folder_path)
		{
			int i = 0;

			stbi_set_flip_vertically_on_load(false);

			std::string skybox_path = use_folder_path ? sFolder + folder_path : folder_path;

			glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &mId);
			glBindTexture(GL_TEXTURE_CUBE_MAP, mId);

			for (const auto& texture : std::filesystem::directory_iterator(skybox_path))
			{
				int width, height, channels;

				stbi_uc* data = stbi_load(texture.path().string().c_str(), &width, &height, &channels, 0);

				if (!data)
				{
					data = stbi_load("../Engine/Assets/Textures/error.png", &width, &height, &channels, 0);
					ENGINE_LOG_WARN("Failed to load the texture : {0}", texture.path().string());
				}

				GLenum internal_format = 0, data_format = 0;
				if (channels == 4)
				{
					internal_format = GL_RGBA8;
					data_format = GL_RGBA;
				}
				else if (channels == 3)
				{
					internal_format = GL_RGB8;
					data_format = GL_RGB;
				}

				ENGINE_ASSERT(internal_format & data_format, "Format not supported!");

				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internal_format, width, height, 0, data_format, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
				++i;
			}

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		}

		CubeMap::~CubeMap()
		{
		}

		void CubeMap::Bind(unsigned int slot) const
		{
			glBindTextureUnit(slot, mId);
		}

		void CubeMap::Unbind() const
		{
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}

		void CubeMap::NoFilter() const
		{}

		void CubeMap::BilinearFilter() const
		{}

		void CubeMap::TrilinearFilter() const
		{}
	}
}