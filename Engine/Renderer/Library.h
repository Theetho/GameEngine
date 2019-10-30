#pragma once

#include "Shader.h"
#include "Texture.h"

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
			const std::string& filePath
		) = 0;

		virtual const Ref<T>& load(
			const std::string& filePath,
			const std::string& name
		) = 0;

		virtual const Ref<T>& get(
			const std::string& name
		) = 0;

		virtual bool exists(
			const std::string& name
		) = 0;
	};

	class ShaderLibrary : Library<Shader>
	{
	public:

		void add(
			const Ref<Shader>& shader
		);

		const Ref<Shader>& load(
			const std::string& filePath
		);

		const Ref<Shader>& load(
			const std::string& filePath,
			const std::string& name
		);

		const Ref<Shader>& get(
			const std::string& name
		);

		inline bool exists(
			const std::string& name
		)
		{
			return m_shaders.find(name) != m_shaders.end();
		}

	private:
		std::unordered_map<std::string, Ref<Shader>> m_shaders;
	};

	class Texture2DLibrary : Library<Texture2D>
	{
	public:
		void add(
			const Ref<Texture2D>& shader
		);

		const Ref<Texture2D>& load(
			const std::string& filePath
		);

		const Ref<Texture2D>& load(
			const std::string& name,
			const std::string& filePath
		);

		const Ref<Texture2D>& get(
			const std::string& name
		);

		inline bool exists(
			const std::string& name
		)
		{
			return m_textures.find(name) != m_textures.end();
		}

	private:
		std::unordered_map<std::string, Ref<Texture2D>> m_textures;
	};
}

