#pragma once

namespace Engine
{

/// Abstract base class

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

/// Texture2D
	
	class Texture2D : public Texture
	{
	public:
		Texture2D(
			const std::string& filePath,
			const std::string& name,
			const bool& useFolderPath
		);

		virtual ~Texture2D()
		{

		}
		
		static Ref<Texture2D> Create(
			const std::string& filePath,
			const std::string& name,
			const bool& useFolderPath
		);
	};

/// OpenGL Texture

	class OpenGLTexture : public Texture2D
	{
	public:
		OpenGLTexture(
			const std::string& filePath,
			const std::string& name,
			const bool& useFolderPath
		);
		
		~OpenGLTexture();

		inline void bind(
			const unsigned int& slot = 0
		) const override
		{
			glBindTextureUnit(slot, m_id);
		}
		
		inline void unbind() const override
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

	private:
		unsigned int m_id;
	};

/// CubeMap

	class CubeMap : public Texture
	{
	public:
		CubeMap(
			const std::string& folderPath,
			const std::string& name,
			const bool& useFolderPath
		);

		virtual ~CubeMap();

		static Ref<CubeMap> Create(
			const std::string& folderPath,
			const std::string& name,
			const bool& useFolderPath
		);
	};

	class OpenGLCubeMap : public CubeMap
	{
	public:
		OpenGLCubeMap(
			const std::string& folderPath,
			const std::string& name,
			const bool& useFolderPath
		);
		~OpenGLCubeMap();

		inline void bind(
			const unsigned int& slot = 0
		) const override
		{
			glBindTextureUnit(slot, m_id);
		}

		inline void unbind() const override
		{
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}

	private:
		unsigned int m_id;
	};
}

