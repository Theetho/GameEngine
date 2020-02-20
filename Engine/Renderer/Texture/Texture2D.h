#pragma once

#include "Texture.h"

namespace Engine
{
	class Shader;

	class Texture2D : public Texture
	{
	public:
		Texture2D(const std::string& file_path, const std::string& name, bool use_folder_path);
		Texture2D(unsigned int width, unsigned int height);
		virtual ~Texture2D();

		virtual unsigned int GetWidth() const;
		virtual unsigned int GetHeight() const;
		virtual Color		 GetPixel(unsigned int x, unsigned int y) const;
		virtual Color		 GetPixel(const Vec2& pixel) const;

		static Ref<Texture2D> Create(const std::string& file_path, const std::string& name = "", bool use_folder_path = true);
		static Ref<Texture2D> Create(unsigned int width, unsigned int height);

		virtual void SetData(unsigned char* data, unsigned int format, unsigned int internal_format) = 0;
	protected:
		unsigned char* mData;
		int mWidth, mHeight, mChannels;
	};
}

