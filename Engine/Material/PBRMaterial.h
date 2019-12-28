#pragma once

#include "Material.h"
#include "Renderer/Texture/Texture2D.h"

namespace Engine
{
	class PBRMaterial : public Material
	{
	public:
		PBRMaterial(
			const std::vector<Ref<Texture2D>>& ambient,
			const std::vector<Ref<Texture2D>>& diffuse,
			const std::vector<Ref<Texture2D>>& specular,
			const std::vector<Ref<Texture2D>>& normal
		);
		~PBRMaterial();

	private:
		std::vector<Ref<Texture2D>> mAmbient;
		std::vector<Ref<Texture2D>> mDiffuse;
		std::vector<Ref<Texture2D>> mSpecular;
		std::vector<Ref<Texture2D>> mNormal;

		int GetID() const override;

		void LoadGLUniforms(Ref<OpenGLShader> shader) override;
	};
}
