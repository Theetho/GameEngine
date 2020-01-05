#pragma once

#include "Texture.h"

namespace Engine
{
	class Texture2D : public Texture
	{
	public:
		Texture2D(const std::string& file_path, const std::string& name, bool use_folder_path);
		virtual ~Texture2D();

		virtual unsigned int GetWidth() const;
		virtual unsigned int GetHeight() const;
		inline virtual Color GetPixel(unsigned int x, unsigned int y) const
		{
			return GetPixel(Vec2(x, y));
		}
		virtual Color		 GetPixel(const Vec2& pixel) const;

		static Ref<Texture2D> Create(const std::string& file_path, const std::string& name = "", bool use_folder_path = true);
	protected:
		unsigned char* mData;
		int mWidth, mHeight, mChannels;
	};
}

