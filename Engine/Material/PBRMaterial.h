#pragma once

#include "Material.h"
#include "Renderer/Texture.h"

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

		~PBRMaterial() {};

	private:
		std::vector<Ref<Texture2D>> m_ambient;
		std::vector<Ref<Texture2D>> m_diffuse;
		std::vector<Ref<Texture2D>> m_specular;
		std::vector<Ref<Texture2D>> m_normal;

		inline const int getID() const override
		{
			return static_cast<int>(MaterialID::PBR);
		}

		void loadGLUniforms(
			Ref<OpenGLShader> shader
		) override;
	};
}
