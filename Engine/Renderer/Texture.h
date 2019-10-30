#pragma once

namespace Engine
{

/// Abstract base class

	class Texture
	{
	public:
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
	
		static void setFolder(
			const std::string& folder
		);

	protected:
		static std::string s_folder;
		unsigned int m_width, m_height;
	};
/// Texture2D
	class Texture2D : public Texture
	{
	public:
		virtual ~Texture2D()
		{

		}
		
		static Ref<Texture2D> create(
			const std::string& texturePath
		);
	};

/// OpenGL Texture

	class OpenGLTexture : public Texture2D
	{
	public:
		OpenGLTexture(
			const std::string& texturePath
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
}

