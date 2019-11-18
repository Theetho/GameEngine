#pragma once

#include "Renderer/Shader.h"

namespace Engine
{
	struct Material
	{
	public:

		void load(
			Ref<Shader> shader
		);

	protected:
		enum class MaterialID
		{
			None,
			Raw,
			PBR
		};

		virtual const int getID() const = 0;
		
		virtual void loadGLUniforms(
			Ref<OpenGLShader> shader
		);

	};
}