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
			GLenum internalFormat = 0, dataFormat = 0;
			if (mChannels == 4)
			{
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
			}
			else if (mChannels == 3)
			{
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
			}

			ENGINE_ASSERT(internalFormat & dataFormat, "Format not supported!");

			glCreateTextures(GL_TEXTURE_2D, 1, &mId);
			glTextureStorage2D(mId, 1, internalFormat, mWidth, mHeight);

			glTextureParameteri(mId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(mId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTextureSubImage2D(mId, 0, 0, 0, mWidth, mHeight, dataFormat, GL_UNSIGNED_BYTE, mData);
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
	}
}