#pragma once

#include "Renderer/Texture/CubeMap.h"

namespace Engine
{
	namespace OpenGL
	{
		class CubeMap : public Engine::CubeMap
		{
		public:
			CubeMap(const std::string& folder_path, const std::string& name, bool use_folder_path);
			~CubeMap();

			void Bind(unsigned int slot = 0) const override;
			void Unbind() const override;

			void NoFilter() const override;
			void BilinearFilter() const override;
			void TrilinearFilter() const override;
		private:
			unsigned int mId;

		};
	}
}

