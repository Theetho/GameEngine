#include "EnginePch.h"
#include "Texture2D.h"
#include <filesystem>
#include "Renderer/Rendering/Renderer.h"
#include "Renderer/Rendering/RendererAPI.h"
#include "API/OpenGL/Texture2D.h"


namespace Engine
{
	Texture2D::Texture2D(const std::string& file_path, const std::string& name, bool use_folder_path)
		: Texture(file_path, name, use_folder_path)
		, mWidth(0)
		, mHeight(0)
	{
		std::string path = use_folder_path ? sFolder + file_path : file_path;

		ENGINE_ASSERT(sFolder != "", "No folder for the textures files");

		//stbi_set_flip_vertically_on_load(true);

		mData = stbi_load(path.c_str(), &mWidth, &mHeight, &mChannels, 0);

		if (!mData)
		{
			mData = stbi_load("../Engine/Assets/Textures/error.png", &mWidth, &mHeight, &mChannels, 0);
			ENGINE_LOG_WARN("Failed to load the texture : {0}", file_path);
		}
	}

	Texture2D::Texture2D(unsigned int width, unsigned int height)
		: Texture()
		, mWidth(width)
		, mHeight(height)
	{}

	Texture2D::~Texture2D()
	{
		stbi_image_free(mData);
	}

	Ref<Texture2D> Texture2D::Create(const std::string& file_path, const std::string& name, bool use_folder_path)
	{
		switch (Renderer::GetAPI())
		{
		case Engine::API::None:
			ENGINE_ASSERT(false, "Api not supported");
		case Engine::API::OpenGL:
			return CreateRef<OpenGL::Texture2D>(file_path, name, use_folder_path);
		}
	}

	Ref<Texture2D> Texture2D::Create(unsigned int width, unsigned int height)
	{
		switch (Renderer::GetAPI())
		{
			case Engine::API::None:
				ENGINE_ASSERT(false, "Api not supported");
			case Engine::API::OpenGL:
				return CreateRef<OpenGL::Texture2D>(width, height);
		}
	}

	Ref<Texture2D> Texture2D::GetWhiteTexture()
	{
		switch (Renderer::GetAPI())
		{
			case Engine::API::None:
				ENGINE_ASSERT(false, "Api not supported");
			case Engine::API::OpenGL:
				return OpenGL::Texture2D::CreateWhiteTexture();
		}
	}

	unsigned int Texture2D::GetWidth() const
	{
		return mWidth;
	}

	unsigned int Texture2D::GetHeight() const
	{
		return mHeight;
	}

	Color Texture2D::GetPixel(unsigned int x, unsigned int y) const
	{
		return GetPixel(Vec2(x, y));
	}

	Color Texture2D::GetPixel(const Vec2& pixel) const
	{
		unsigned char red, green, blue, alpha;
		unsigned char* pixel_offset = mData + ((int)pixel.x + mHeight * (int)pixel.y) * mChannels;

		red   = pixel_offset[0];
		green = pixel_offset[1];
		blue  = pixel_offset[2];
		alpha = mChannels == 4 ? pixel_offset[3] : 255;

		return Color(red, green, blue, alpha);
	}
}