#pragma once

namespace Engine
{
	class Texture
	{
	public:
		Texture(
			const std::string& filePath,
			const std::string& name,
			const bool& useFolderPath
		);

		virtual ~Texture()
		{

		}

		virtual void bind(
			const unsigned int& slot = 0
		) const = 0;  
		
		virtual void unbind() const = 0;
	
		unsigned int getWidth() const
		{
			return m_width;
		}

		unsigned int getHeight() const
		{
			return m_height;
		}
	
		inline static void setFolder(
			const std::string& folder
		)
		{
			s_folder = folder;
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
		static std::string s_folder;
		std::string m_name;
		unsigned int m_width, m_height;
	};
}

