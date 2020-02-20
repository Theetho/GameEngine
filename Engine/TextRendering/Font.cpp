#include "EnginePch.h"
#include "Font.h"
#include "API/OpenGL/Texture2D.h"

using namespace ftgl;

namespace Engine
{
	Font::Font(const char* path, float size)
		: mAtlas()
		, mFont()
		, mAtlasTexture(nullptr)
	{
		mAtlas = texture_atlas_new(512, 512, 3);
		mFont = texture_font_new_from_file(mAtlas, size, path);
		texture_font_load_glyphs(mFont, " !\"#$%&'()*+,-./0123456789:;<=>?");
		texture_font_load_glyphs(mFont, "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_");
		texture_font_load_glyphs(mFont, "`abcdefghijklmnopqrstuvwxyz{ |}~");
		mAtlasTexture = CreateRef<OpenGL::Texture2D>(512, 512);
		mAtlasTexture->SetData(mAtlas->data, GL_RGB, GL_RGB);
	}

	Ref<Texture2D> Font::GetTextureAtlas() const
	{
		return mAtlasTexture;
	}
}
