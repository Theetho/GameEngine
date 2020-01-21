#pragma once

#include "Renderer/Texture/Texture2D.h"

namespace Engine
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& file_path, const std::string& name, bool use_folder_path);
		OpenGLTexture2D(unsigned int width, unsigned int height, unsigned int id = 0);
		~OpenGLTexture2D();

		void Bind(unsigned int slot = 0) const override;
		void Unbind() const override;
	private:
		unsigned int mId;
	};
}

