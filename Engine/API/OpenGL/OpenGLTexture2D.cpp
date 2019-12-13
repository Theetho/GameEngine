#include "EnginePch.h"
#include "OpenGLTexture2D.h"
#include "Core/Log.h"

namespace Engine
{
	OpenGLTexture2D::OpenGLTexture2D(
		const std::string& filePath,
		const std::string& name,
		const bool& useFolderPath
	)
		: Texture2D(filePath, name, useFolderPath)
		, m_id(0)
	{
		ENGINE_ASSERT(s_folder != "", "No folder for the textures files");

		stbi_set_flip_vertically_on_load(true);

		int w, h, c;
		stbi_uc* data = useFolderPath ?
			stbi_load((s_folder + filePath).c_str(), &w, &h, &c, 0)
			: 
			stbi_load((filePath).c_str(), &w, &h, &c, 0)
		;
		
		if (!data)
		{
			data = stbi_load("../Engine/Assets/Textures/error.png", &w, &h, &c, 0);
			ENGINE_LOG_WARN("Failed to load the texture : {0}", filePath);
		}
		
		m_width  = w;
		m_height = h;

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

		glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
		glTextureStorage2D(m_id, 1, internalFormat, m_width, m_height);

		glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, dataFormat, GL_UNSIGNED_BYTE, data);
	
		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_id);
	}
}