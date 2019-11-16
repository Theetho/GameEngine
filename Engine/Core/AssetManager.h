#pragma once

#include "Renderer/Library.h"

namespace Engine
{
	class AssetManager
	{
	public:
		inline static ShaderLibrary& getShaderLibrary()
		{
			return s_shaderLibrary;
		}

		inline static Texture2DLibrary& getTexture2DLibrary()
		{
			return s_texture2DLibrary;
		}

		inline static ModelLibrary& getModelLibrary()
		{
			return s_modelLibrary;
		}
	private:
		static ShaderLibrary s_shaderLibrary;
		static Texture2DLibrary s_texture2DLibrary;
		static ModelLibrary s_modelLibrary;
	};
}

