#pragma once

#include "API/OpenGL/OpenGLShader.h"

namespace Engine
{
	class Material
	{
	public:
		void Load(Ref<Shader> shader);
	protected:
		enum class MaterialID
		{
			None,
			Raw,
			PBR
		};

		virtual int  GetID() const = 0;
		
		virtual void LoadGLUniforms(Ref<OpenGLShader> shader);
	};
}