#pragma once

#include "Texture.h"

namespace Engine
{
	class Texture2D : public Texture
	{
	public:
		Texture2D(
			const std::string& filePath,
			const std::string& name,
			const bool& useFolderPath
		);

		virtual ~Texture2D()
		{

		}

		static Ref<Texture2D> Create(
			const std::string& filePath,
			const std::string& name,
			const bool& useFolderPath
		);
	};
}

