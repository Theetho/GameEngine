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
		mAtlas = texture_atlas_new(512, 512, 1);
		mFont = texture_font_new_from_file(mAtlas, size, path);

		ftgl::texture_font_load_glyph(mFont, "A");
		std::cout << mAtlas->data << std::endl;
		mAtlasTexture = CreateRef<OpenGL::Texture2D>(512, 512);
		std::dynamic_pointer_cast<OpenGL::Texture2D>(mAtlasTexture)->SetId(mAtlas->id);
		mAtlasTexture->SetData(mAtlas->data, GL_RGBA);
	}

	Ref<Texture2D> Font::GetTextureAtlas() const
	{
		return mAtlasTexture;
	}
}
