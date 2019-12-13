#pragma once

#include "Renderer/Texture/Texture2D.h"

namespace Engine
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(
			const std::string& filePath,
			const std::string& name,
			const bool& useFolderPath
		);
		
		~OpenGLTexture2D();

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

