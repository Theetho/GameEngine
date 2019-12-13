#pragma once

#include "Renderer/Texture/CubeMap.h"

namespace Engine
{
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

