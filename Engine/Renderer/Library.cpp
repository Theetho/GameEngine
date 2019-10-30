#include "EnginePch.h"
#include "Library.h"
#include "Core/Log.h"

namespace Engine
{
	
/// Shader library class

	void ShaderLibrary::add(
		const Ref<Shader>& shader
	)
	{
		if (!exists(shader->getName()))
			m_shaders[shader->getName()] = shader;
		else
			ENGINE_LOG_WARN(
				"Shader \"{0}\" already exists",
				shader->getName()
			);
	}

	const Ref<Shader>& ShaderLibrary::load(
		const std::string& filePath
	)
	{
		auto shader = Shader::create(filePath);

		if (!exists(shader->getName()))
		{
			m_shaders[shader->getName()] = shader;
			return m_shaders[shader->getName()];
		}
		else
		{
			ENGINE_LOG_WARN(
				"Shader \"{0}\" already exists",
				shader->getName()
			);
		}
	}

	const Ref<Shader>& ShaderLibrary::load(
		const std::string& filePath, 
		const std::string& name
	)
	{
		if (!exists(name))
		{
			m_shaders[name] = Shader::create(filePath);

			m_shaders[name]->setName(name);

			return m_shaders[name];
		}
		else
		{
			ENGINE_LOG_WARN(
				"Shader \"{0}\" already exists",
				name
			);
		}
	}

	const Ref<Shader>& ShaderLibrary::get(
		const std::string& name
	)
	{
		if (exists(name))
		{
			return m_shaders[name];
		}
		else
		{
			ENGINE_LOG_WARN(
				"Shader \"{0}\" doesn't exist",
				name
			);
		}
	}

/// Texture2D library class

	void Texture2DLibrary::add(
		const Ref<Texture2D>& texture
	)
	{
		if (!exists(texture->getName()))
			m_textures[texture->getName()] = texture;
		else
			ENGINE_LOG_WARN(
				"Texture2D \"{0}\" already exists",
				texture->getName()
			);
	}

	const Ref<Texture2D>& Texture2DLibrary::load(
		const std::string& filePath
	)
	{
		auto texture = Texture2D::create(filePath);

		if (!exists(texture->getName()))
		{
			m_textures[texture->getName()] = texture;
			return m_textures[texture->getName()];
		}
		else
		{
			ENGINE_LOG_WARN(
				"Texture2D \"{0}\" already exists",
				texture->getName()
			);
		}
	}

	const Ref<Texture2D>& Texture2DLibrary::load(
		const std::string& filePath, 
		const std::string& name
	)
	{
		if (!exists(name))
		{
			m_textures[name] = Texture2D::create(filePath);

			m_textures[name]->setName(name);

			return m_textures[name];
		}
		else
		{
			ENGINE_LOG_WARN(
				"Texture2D \"{0}\" already exists",
				name
			);
		}
	}

	const Ref<Texture2D>& Texture2DLibrary::get(
		const std::string& name
	)
	{
		if (exists(name))
		{
			return m_textures[name];
		}
		else
		{
			ENGINE_LOG_WARN(
				"Texture2D \"{0}\" doesn't exist",
				name
			);
		}
	}
}