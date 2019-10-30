#include "EnginePch.h"
#include "Texture.h"
#include "Renderer.h"

namespace Engine
{

/// Abstract base class

	std::string Texture::s_folder = "";

	void Texture::setFolder(const std::string& folder)
	{
		s_folder = folder;
	}

/// Texture2D

	Ref<Texture2D> Texture2D::create(
		const std::string& texturePath
	)
	{
		switch (Renderer::getAPI())
		{
		case Engine::API::None:
			ENGINE_ASSERT(false, "Api not supported");
		case Engine::API::OpenGL:
			return std::make_shared<OpenGLTexture>(texturePath);
		}
	}

/// OpenGL Texture

	OpenGLTexture::OpenGLTexture(
		const std::string& texturePath
	)
		: m_id(0)
	{
		ENGINE_ASSERT(s_folder != "", "No folder for the textures files");

		stbi_set_flip_vertically_on_load(1);

		int w, h, c;
		stbi_uc* data = stbi_load((s_folder + texturePath).c_str(), &w, &h, &c, 0);
		ENGINE_ASSERT(data, "Failed to load the texture");
		
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

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_id);
	}
}