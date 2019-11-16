#pragma once

#include "Shader.h"
#include "Texture.h"
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
		) = 0;

		virtual const Ref<T>& load(
			const std::string& filePath,
			std::string name = "",
			const bool& useFolderPath = true
		) = 0;

		virtual const Ref<T>& get(
			const std::string& name
		) = 0;

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
			auto lastSlash = filePath.find_last_of("/\\");
			lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
			auto lastDot = filePath.rfind('.');
			int count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;

			return filePath.substr(lastSlash, count);
		}
	};

	class ShaderLibrary : Library<Shader>
	{
	public:

		void add(
			const Ref<Shader>& shader
		);

		const Ref<Shader>& load(
			const std::string& filePath,
			std::string name = "",
			const bool& useFolderPath = true
		);

		const Ref<Shader>& get(
			const std::string& name
		);
	};

	class Texture2DLibrary : Library<Texture2D>
	{
	public:
		void add(
			const Ref<Texture2D>& shader
		);

		const Ref<Texture2D>& load(
			const std::string& filePath,
			std::string name = "",
			const bool& useFolderPath = true
		);

		const Ref<Texture2D>& get(
			const std::string& name
		);
	};

	class ModelLibrary : public Library<Model>
	{
	public:
		void add(
			const Ref<Model>& model
		) override;

		const Ref<Model>& load(
			const std::string& filePath,
			std::string name = "",
			const bool& useFolderPath = true
		) override;

		const Ref<Model>& get(
			const std::string& name
		) override;
	};
}

