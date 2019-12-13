#pragma once

#include "Include/Maths.h"

namespace Engine
{
	class Shader
	{
	public:
		Shader(
			const std::string& filePath,
			const std::string& name,
			const bool& useFolderPath
		);

		virtual ~Shader() 
		{
		}

		virtual void bind() const = 0;

		virtual void unbind() const = 0;

		static Ref<Shader> Create(
			const std::string& filePath,
			const std::string& name,
			const bool& useFolderPath
		);

		static void setFolder(
			const std::string& folderPath
		)
		{
			s_folderPath = folderPath;
		}

		inline virtual void setName(
			const std::string& name
		)
		{
			m_name = name;
		}
		
		inline virtual std::string getName() const
		{
			return m_name;
		}

	protected:
		virtual void readFile(
			const std::string& filePath
		) = 0;
		static std::string s_folderPath;
		std::string m_name;
	};
}

