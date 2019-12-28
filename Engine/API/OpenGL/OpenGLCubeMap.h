#pragma once

#include "Renderer/Texture/CubeMap.h"

namespace Engine
{
	class OpenGLCubeMap : public CubeMap
	{
	public:
		OpenGLCubeMap(const std::string& folder_path, const std::string& name, bool use_folder_path);
		~OpenGLCubeMap();

		void Bind(unsigned int slot = 0) const override;
		void Unbind() const override;

	private:
		unsigned int mId;
	};
}

