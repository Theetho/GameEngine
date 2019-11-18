#include "EnginePch.h"
#include "PBRMaterial.h"

namespace Engine
{
	PBRMaterial::PBRMaterial(
		const std::vector<Ref<Texture2D>>& ambient,
		const std::vector<Ref<Texture2D>>& diffuse,
		const std::vector<Ref<Texture2D>>& specular,
		const std::vector<Ref<Texture2D>>& normal
	)
		: m_ambient(ambient)
		, m_diffuse(diffuse)
		, m_specular(specular)
		, m_normal(normal)
	{
	}

	void PBRMaterial::loadGLUniforms(
		Ref<OpenGLShader> shader
	)
	{
		Material::loadGLUniforms(shader);

		int textureUnit = 0;
		for (int i = 0; i < m_ambient.size(); ++i)
		{
			m_ambient[i]->bind(textureUnit);
			shader->uploadUniform("u_material.texture_am" + std::to_string(i), textureUnit++);
		}
		for (int i = 0; i < m_diffuse.size(); ++i)
		{
			m_diffuse[i]->bind(textureUnit);
			shader->uploadUniform("u_material.texture_df" + std::to_string(i), textureUnit++);
		}
		for (int i = 0; i < m_specular.size(); ++i)
		{
			m_specular[i]->bind(textureUnit);
			shader->uploadUniform("u_material.texture_sp" + std::to_string(i), textureUnit++);
		}
		for (int i = 0; i < m_normal.size(); ++i)
		{
			m_normal[i]->bind(textureUnit);
			shader->uploadUniform("u_material.texture_nl" + std::to_string(i), textureUnit++);
		}
	}
}