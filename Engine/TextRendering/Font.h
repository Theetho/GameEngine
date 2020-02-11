#pragma once

namespace Engine
{
	class Font
	{
	public:
		Font(const char* path, unsigned int size);
	private:
		static FT_Library sFreeTypeLibrary;
		FT_Face mFace;

		struct Character
		{
			char character;
			unsigned char* data;
			unsigned int width, height;
			Vec2 bearing;
			unsigned int advance;
			Character(char c, unsigned char* d, unsigned int w, unsigned int h, Vec2 b, unsigned int a)
				: character(c), data(d), width(w), height(h), bearing(b), advance(a)
			{}
		};
		std::vector<Character> mGlyphes;
	};
}

