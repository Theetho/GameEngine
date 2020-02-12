#pragma once

namespace Engine
{
	class Texture2D;

	class Font
	{
	public:
		Font(const char* path, float size);

		Ref<Texture2D> GetTextureAtlas() const;
	private:
		ftgl::texture_atlas_t* mAtlas;
		ftgl::texture_font_t*  mFont;
		Ref<Texture2D> mAtlasTexture;
	};
}

