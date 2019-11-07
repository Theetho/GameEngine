#include "EnginePch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Core/Log.h"

namespace Engine
{

/// Abstract base class

	std::string Texture::s_folder = "";

	Texture::Texture(
		const std::string& filePath,
		const std::string& name
	)
		: m_name(name)
		, m_width(0)
		, m_height(0)
	{
		// Setting the name of the shader
		if (m_name == "")
		{
			auto lastSlash = filePath.find_last_of("/\\");
			lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
			auto lastDot = filePath.rfind('.');
			int count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;

			m_name = filePath.substr(lastSlash, count);
		}
	}

/// Texture2D

	Texture2D::Texture2D(
		const std::string& filePath,
		const std::string& name
	)
		: Texture(filePath, name)
	{
	}

	Ref<Texture2D> Texture2D::Create(
		const std::string& filePath,
		const std::string& name
	)
	{
		switch (Renderer::getAPI())
		{
		case Engine::API::None:
			ENGINE_ASSERT(false, "Api not supported");
		case Engine::API::OpenGL:
			return std::make_shared<OpenGLTexture>(filePath, name);
		}
	}

/// OpenGL Texture

	OpenGLTexture::OpenGLTexture(
		const std::string& filePath,
		const std::string& name
	)
		: Texture2D(filePath, name)
		, m_id(0)
	{
		ENGINE_ASSERT(s_folder != "", "No folder for the textures files");

		stbi_set_flip_vertically_on_load(1);

		int w, h, c;
		stbi_uc* data = stbi_load((s_folder + filePath).c_str(), &w, &h, &c, 0);
		
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

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_id);
	}
}