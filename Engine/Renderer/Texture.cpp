#include "EnginePch.h"
#include "Texture.h"
#include <filesystem>
#include "Renderer.h"
#include "Core/Log.h"

namespace Engine
{

/// Abstract base class

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
		const std::string& name,
		const bool& useFolderPath
	)
		: Texture(filePath, name, useFolderPath)
	{
	}

	Ref<Texture2D> Texture2D::Create(
		const std::string& filePath,
		const std::string& name,
		const bool& useFolderPath
	)
	{
		switch (Renderer::getAPI())
		{
		case Engine::API::None:
			ENGINE_ASSERT(false, "Api not supported");
		case Engine::API::OpenGL:
			return std::make_shared<OpenGLTexture>(filePath, name, useFolderPath);
		}
	}

/// OpenGL Texture

	OpenGLTexture::OpenGLTexture(
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

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_id);
	}

/// Cube map

	CubeMap::CubeMap(
		const std::string& folderPath,
		const std::string& name,
		const bool& useFolderPath
	)
		: Texture(folderPath, name, useFolderPath)
	{
	}

	CubeMap::~CubeMap()
	{
	}

	Ref<CubeMap> CubeMap::Create(const std::string& filePath, const std::string& name, const bool& useFolderPath)
	{
		switch (Renderer::getAPI())
		{
		case Engine::API::None:
			ENGINE_ASSERT(false, "Api not supported");
		case Engine::API::OpenGL:
			return std::make_shared<OpenGLCubeMap>(filePath, name, useFolderPath);
		}
	}

/// OpenGL Cube Map

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