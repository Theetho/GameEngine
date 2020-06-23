#include "EnginePch.h"
#include "AssetManager.h"

namespace Engine
{
	ShaderLibrary	 AssetManager::sShaderLibrary;
	Texture2DLibrary AssetManager::sTexture2DLibrary;
	MeshLibrary		 AssetManager::sMeshLibrary;

	ShaderLibrary& AssetManager::GetShaderLibrary()
	{
		return sShaderLibrary;
	}
	
	Texture2DLibrary& AssetManager::GetTexture2DLibrary()
	{
		return sTexture2DLibrary;
	}
	
	MeshLibrary& AssetManager::GetMeshLibrary()
	{
		return sMeshLibrary;
	}
}