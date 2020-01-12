#pragma once

#include "Renderer/Library.h";

namespace Engine
{
	class AssetManager
	{
	public:
		static ShaderLibrary&    GetShaderLibrary();
		static Texture2DLibrary& GetTexture2DLibrary();
		static ModelLibrary&	 GetModelLibrary();
	private:
		static ShaderLibrary sShaderLibrary;
		static Texture2DLibrary sTexture2DLibrary;
		static ModelLibrary sModelLibrary;
	};
}

