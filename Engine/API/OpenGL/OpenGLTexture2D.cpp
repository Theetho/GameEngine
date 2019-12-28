#include "EnginePch.h"
#include "OpenGLTexture2D.h"
#include "Core/Log.h"

namespace Engine
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& file_path, const std::string& name, bool use_folder_path)
		: Texture2D(file_path, name, use_folder_path)
		, mId(0)
	{
		ENGINE_ASSERT(sFolder != "", "No folder for the textures files");

		stbi_set_flip_vertically_on_load(true);

		int width, height, channels;
		stbi_uc* data = use_folder_path ? stbi_load((sFolder + file_path).c_str(), &width, &height, &channels, 0) : stbi_load((file_path).c_str(), &width, &height, &channels, 0);
		
		if (!data)
		{
			data = stbi_load("../Engine/Assets/Textures/error.png", &width, &height, &channels, 0);
			ENGINE_LOG_WARN("Failed to load the texture : {0}", file_path);
		}
		
		mWidth  = width;
		mHeight = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		ENGINE_ASSERT(internalFormat & dataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &mId);
		glTextureStorage2D(mId, 1, internalFormat, mWidth, mHeight);

		glTextureParameteri(mId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(mId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(mId, 0, 0, 0, mWidth, mHeight, dataFormat, GL_UNSIGNED_BYTE, data);
	
		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &mId);
	}

	void OpenGLTexture2D::Bind(unsigned int slot) const
	{
		glBindTextureUnit(slot, mId);
	}

	void OpenGLTexture2D::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}