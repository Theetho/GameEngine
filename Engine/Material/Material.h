#pragma once

#include "Core/SceneObject.h"

namespace Engine
{
	class Shader;
	namespace OpenGL
	{
		class Shader;
	}

	class Material : public SceneObject
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
		virtual void LoadGLUniforms(Ref<OpenGL::Shader> shader);
	};
}