#include "EnginePch.h"
#include "Font.h"
#include "API/OpenGL/Texture2D.h"
#include "Core/Application.h"
#include "Core/Window.h"

#define FONT_TEXTURE_MULTIPLIER 6.0f

using namespace ftgl;

namespace Engine
{
	Font::Font(const char* path, float size)
		: mAtlas()
		, mFont()
		, mAtlasTexture(nullptr)
		, mScale(Application::Get().GetWindow().GetWidth() / 2.0f, Application::Get().GetWindow().GetHeight() / 1.375f)
	{
		Vec2 dimensions(size * FONT_TEXTURE_MULTIPLIER);
		mAtlas = texture_atlas_new(dimensions.x, dimensions.y, 1);
		mFont = texture_font_new_from_file(mAtlas, size, path);
		texture_font_load_glyphs(mFont, " !\"#$%&'()*+,-./0123456789:;<=>?");
		texture_font_load_glyphs(mFont, "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_");
		texture_font_load_glyphs(mFont, "`abcdefghijklmnopqrstuvwxyz{ |}~");
		mAtlasTexture = CreateRef<OpenGL::Texture2D>(dimensions.x, dimensions.y);
		mAtlasTexture->SetData(mAtlas->data, GL_ALPHA, GL_ALPHA);//GL_RGB, GL_RGB);
	}

	void Font::SetScale(float x, float y)
	{
		mScale = { x, y };
	}

	void Font::SetScale(const Vec2& scale)
	{
		mScale = scale;
	}

	const Vec2& Font::GetScale() const
	{
		return mScale;
	}

	Ref<Texture2D> Font::GetTextureAtlas() const
	{
		return mAtlasTexture;
	}
	
	ftgl::texture_font_t* Font::GetFTFont()
	{
		return mFont;
	}
}
