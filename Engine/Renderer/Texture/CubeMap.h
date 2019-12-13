#pragma once

#include "Texture.h"

namespace Engine
{
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
}

