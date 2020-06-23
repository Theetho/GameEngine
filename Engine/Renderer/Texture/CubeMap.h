#pragma once

#include "Texture.h"

namespace Engine
{
	class CubeMap : public Texture
	{
	public:
		CubeMap(const std::string& folder_path);
		virtual ~CubeMap();

		static Ref<CubeMap> Create(const std::string& folder_path);
	};
}

