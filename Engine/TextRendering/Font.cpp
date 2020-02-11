#include "EnginePch.h"
#include "Font.h"

using namespace ftgl;

namespace Engine
{
	Font::Font(const char* path, float size)
		: mAtlas(texture_atlas_new(512, 512, 1))
		, mFont(texture_font_new_from_file(mAtlas, size, path))
	{}
}
