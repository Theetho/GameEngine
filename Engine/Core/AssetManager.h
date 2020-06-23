#pragma once

#include "Renderer/Library.h"

namespace Engine
{
	class AssetManager
	{
	public:
		static ShaderLibrary&    GetShaderLibrary();
		static Texture2DLibrary& GetTexture2DLibrary();
		static MeshLibrary&	     GetMeshLibrary();
	private:
		static ShaderLibrary	sShaderLibrary;
		static Texture2DLibrary sTexture2DLibrary;
		static MeshLibrary		sMeshLibrary;
	};
}

