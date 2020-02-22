#pragma once

namespace Engine
{
	class Texture2D;

	class Font
	{
	public:
		Font(const char* path, float size);

		void SetScale(float x, float y);
		void SetScale(const Vec2& scale);

		const Vec2& GetScale() const;
		Ref<Texture2D> GetTextureAtlas() const;
		ftgl::texture_font_t* GetFTFont();
	private:
		ftgl::texture_atlas_t* mAtlas;
		ftgl::texture_font_t*  mFont;
		Ref<Texture2D> mAtlasTexture;
		Vec2 mScale;
	};
}

