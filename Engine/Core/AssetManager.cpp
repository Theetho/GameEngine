#include "EnginePch.h"
#include "AssetManager.h"

namespace Engine
{
	ShaderLibrary	 AssetManager::sShaderLibrary;
	Texture2DLibrary AssetManager::sTexture2DLibrary;
	ModelLibrary	 AssetManager::sModelLibrary;

	ShaderLibrary& AssetManager::GetShaderLibrary()
	{
		return sShaderLibrary;
	}
	
	Texture2DLibrary& AssetManager::GetTexture2DLibrary()
	{
		return sTexture2DLibrary;
	}
	
	ModelLibrary& AssetManager::GetModelLibrary()
	{
		return sModelLibrary;
	}
}