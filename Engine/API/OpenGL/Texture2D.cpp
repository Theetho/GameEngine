#include "EnginePch.h"
#include "Texture2D.h"

namespace Engine
{
	namespace OpenGL
	{
		Texture2D::Texture2D(const std::string& file_path, const std::string& name, bool use_folder_path)
			: Engine::Texture2D(file_path, name, use_folder_path)
			, mId(0)
		{
			GLenum dataFormat = 0;
			if (mChannels == 4)
				dataFormat = GL_RGBA;
			else if (mChannels == 3)
				dataFormat = GL_RGB;

			ENGINE_ASSERT(dataFormat, "Format not supported!");

			glGenTextures(1, &mId);
			glBindTexture(GL_TEXTURE_2D, mId);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			
			glTexImage2D(GL_TEXTURE_2D, 0, dataFormat, mWidth, mHeight, 0, dataFormat, GL_UNSIGNED_BYTE, mData);
			glGenerateMipmap(GL_TEXTURE_2D);
			
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		Texture2D::Texture2D(unsigned int width, unsigned int height, unsigned int id)
			: Engine::Texture2D(width, height)
			, mId(id)
		{
		}

		Texture2D::~Texture2D()
		{
			glDeleteTextures(1, &mId);
		}

		void Texture2D::Bind(unsigned int slot) const
		{
			glBindTextureUnit(slot, mId);
		}

		void Texture2D::Unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void Texture2D::TrilinearFilter() const
		{
			glBindTexture(GL_TEXTURE_2D, mId);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glGenerateTextureMipmap(GL_TEXTURE_2D);
		}
	}
}