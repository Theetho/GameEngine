#pragma once

namespace Engine
{
	class Font
	{
	public:
		Font(const char* path, float size);
	private:
		ftgl::texture_atlas_t* mAtlas;
		ftgl::texture_font_t*  mFont;
	};
}

