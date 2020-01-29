#pragma once

#include "Renderer/Texture/Texture2D.h"

namespace Engine
{
	namespace OpenGL
	{
		class Texture2D : public Engine::Texture2D
		{
		public:
			Texture2D(const std::string& file_path, const std::string& name, bool use_folder_path);
			Texture2D(unsigned int width, unsigned int height, unsigned int id = 0);
			~Texture2D();

			void Bind(unsigned int slot = 0) const override;
			void Unbind() const override;

			void TrilinearFilter() const override;
		private:
			unsigned int mId;
		};
	}
}

