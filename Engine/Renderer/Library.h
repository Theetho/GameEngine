#pragma once

#include "Shader.h"
#include "Texture/Texture2D.h"
#include "Model/Model.h"

namespace Engine
{
	template<typename T>
	class Library
	{
	public:
		virtual ~Library()
		{
		}

		virtual void add(
			const Ref<T>& t
		)
		{
			if (!exists(t->getName()))
				m_references[t->getName()] = t;
		}

		virtual const Ref<T>& load(
			const std::string& filePath,
			std::string name = "",
			const bool& useFolderPath = true
		)
		{
			if (name == "")
				name = extractName(filePath);

			if (!exists(name))
			{
				m_references[name] = T::Create(filePath, name, useFolderPath);
			}

			return m_references[name];
		}

		virtual const Ref<T>& get(
			const std::string& name
		)
		{
			if (exists(name))
			{
				return m_references[name];
			}
		}

		virtual bool exists(
			const std::string& name
		)
		{
			return m_references.find(name) != m_references.end();
		}
	protected:
		std::unordered_map<std::string, Ref<T>> m_references;

		inline std::string extractName(
			const std::string& filePath
		)
		{
			// Getting the name from the file path
			size_t lastSlash = filePath.find_last_of("/\\");
			lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
			size_t lastDot = filePath.rfind('.');
			int count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;

			return filePath.substr(lastSlash, count);
		}
	};

	typedef Library<Shader> ShaderLibrary;
	typedef Library<Texture2D> Texture2DLibrary;
	typedef Library<Model> ModelLibrary;
}

