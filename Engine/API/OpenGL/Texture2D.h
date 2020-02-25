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

			void SetData(unsigned char* data, unsigned int format, unsigned int internal_format) override;
			void Bind(unsigned int slot = 0) const override;
			void Unbind() const override;

			void NoFilter() const override;
			void BilinearFilter() const override;
			void TrilinearFilter() const override;

			void SetId(unsigned int id);
			uint GetId() const override;
		private:
			unsigned int mId;

			friend class Engine::Texture2D;
			static Ref<Texture2D> CreateWhiteTexture();
		};
	}
}

