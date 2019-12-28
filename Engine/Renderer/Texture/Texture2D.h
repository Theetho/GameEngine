#pragma once

#include "Texture.h"

namespace Engine
{
	class Texture2D : public Texture
	{
	public:
		Texture2D(const std::string& file_path, const std::string& name, bool use_folder_path);
		virtual ~Texture2D();

		static Ref<Texture2D> Create(const std::string& file_path, const std::string& name, bool use_folder_path);
	};
}

