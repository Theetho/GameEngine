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
			m_references[shader->getName()] = shader;
		else
			ENGINE_LOG_WARN(
				"Shader \"{0}\" already exists",
				shader->getName()
			);
	}
	const Ref<Shader>& ShaderLibrary::load(
		const std::string& filePath, 
		std::string name,
		const bool& useFolderPath
	)
	{	
		if (name == "")
			name = extractName(filePath);

		if (!exists(name))
		{
			m_references[name] = Shader::Create(filePath, name, useFolderPath);
		}
		else
		{
			ENGINE_LOG_WARN(
				"Shader \"{0}\" already exists",
				name
			);
		}

		return m_references[name];
	}

	const Ref<Shader>& ShaderLibrary::get(
		const std::string& name
	)
	{
		if (exists(name))
		{
			return m_references[name];
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
			m_references[texture->getName()] = texture;
		else
			ENGINE_LOG_WARN(
				"Texture2D \"{0}\" already exists",
				texture->getName()
			);
	}

	const Ref<Texture2D>& Texture2DLibrary::load(
		const std::string& filePath, 
		std::string name,
		const bool& useFolderPath
	)
	{
		if (name == "")
			name = extractName(filePath);

		if (!exists(name))
		{
			m_references[name] = Texture2D::Create(filePath, name, useFolderPath);
		}
		else
		{
			ENGINE_LOG_WARN(
				"Texture2D \"{0}\" already exists",
				name
			);
		}

		return m_references[name];
	}

	const Ref<Texture2D>& Texture2DLibrary::get(
		const std::string& name
	)
	{
		if (exists(name))
		{
			return m_references[name];
		}
		else
		{
			ENGINE_LOG_WARN(
				"Texture2D \"{0}\" doesn't exist",
				name
			);
		}
	}

/// Model library


	void ModelLibrary::add(
		const Ref<Model>& model
	)
	{
		if (!exists(model->getName()))
			m_references[model->getName()] = model;
		else
			ENGINE_LOG_WARN(
				"Shader \"{0}\" already exists",
				model->getName()
			);
	}

	const Ref<Model>& ModelLibrary::load(
		const std::string& filePath,
		std::string name,
		const bool& useFolderPath
	)
	{
		if (name == "")
			name = extractName(filePath);

		if (!exists(name))
		{
			auto model = Model::Create(filePath, name, useFolderPath);
			m_references[name] = model;
		}
		else
		{
			ENGINE_LOG_WARN(
				"Texture2D \"{0}\" already exists",
				name
			);
		}

		return m_references[name];
	}

	const Ref<Model>& ModelLibrary::get(
		const std::string& name
	)
	{
		if (exists(name))
		{
			return m_references[name];
		}
		else
		{
			ENGINE_LOG_WARN(
				"Model \"{0}\" doesn't exist",
				name
			);
		}
	}
}