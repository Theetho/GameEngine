#include "EnginePch.h"
#include "Font.h"

namespace Engine
{
	FT_Library Font::sFreeTypeLibrary;

	Font::Font(const char* path, unsigned int size)
	{
		static bool is_initialized = false;
		if (!is_initialized)
		{
			if (FT_Init_FreeType(&sFreeTypeLibrary))
				ENGINE_LOG_ERROR("ERROR::FREETYPE: Could not init FreeType Library");
			is_initialized = true;
		}

		if (FT_New_Face(sFreeTypeLibrary, path, 0, &mFace))
			ENGINE_LOG_ERROR("ERROR::FREETYPE: Failed to load font {0}", path);

		FT_Set_Pixel_Sizes(mFace, 0, size);

		for (unsigned char character = 0; character < 128; ++character)
		{
			if (FT_Load_Char(mFace, character, FT_LOAD_RENDER))
			{
				ENGINE_LOG_ERROR("ERROR::FREETYTPE: Failed to load the glyph {0}", character);
				continue;
			}

			mGlyphes.push_back(std::move(Character(
				character,
				mFace->glyph->bitmap.buffer,
				mFace->glyph->bitmap.width,
				mFace->glyph->bitmap.rows,
				std::move(Vec2(mFace->glyph->bitmap_left, mFace->glyph->bitmap_top)),
				mFace->glyph->advance.x
			)));
		}
	}
}
