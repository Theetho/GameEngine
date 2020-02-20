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
			GLenum internal_format = 0, format = 0;
			if (mChannels == 4)
			{
				internal_format = GL_RGBA;
				format = GL_RGBA;
			}
			else if (mChannels == 3)
			{
				format = GL_RGB;
				internal_format = GL_RGB;
			}

			ENGINE_ASSERT(dataFormat, "Format not supported!");

			glGenTextures(1, &mId);
			this->SetData(mData, format, internal_format);
		}

		Texture2D::Texture2D(unsigned int width, unsigned int height, unsigned int id)
			: Engine::Texture2D(width, height)
			, mId(id)
		{
			glBindTexture(GL_TEXTURE_2D, mId);
		}

		Texture2D::~Texture2D()
		{
			glDeleteTextures(1, &mId);
		}

		void Texture2D::SetData(unsigned char* data, unsigned int format, unsigned int internal_format)
		{
			if (!mId)
				glGenTextures(1, &mId);

			mData = data;
			glBindTexture(GL_TEXTURE_2D, mId);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, internal_format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void Texture2D::Bind(unsigned int slot) const
		{
			glBindTextureUnit(slot, mId);
		}

		void Texture2D::Unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void Texture2D::NoFilter() const
		{
			glBindTexture(GL_TEXTURE_2D, mId);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}

		void Texture2D::BilinearFilter() const
		{
			glBindTexture(GL_TEXTURE_2D, mId);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}

		void Texture2D::TrilinearFilter() const
		{
			glBindTexture(GL_TEXTURE_2D, mId);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glGenerateTextureMipmap(GL_TEXTURE_2D);
		}

		void Texture2D::SetId(unsigned int id)
		{
			mId = id;
		}

		unsigned int Texture2D::GetId() const
		{
			return mId;
		}
	}
}