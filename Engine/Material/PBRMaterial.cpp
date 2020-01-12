#include "EnginePch.h"
#include "PBRMaterial.h"
#include "API/OpenGL/OpenGLShader.h"
#include "Renderer/Texture/Texture2D.h"

namespace Engine
{
	PBRMaterial::PBRMaterial(
		const std::vector<Ref<Texture2D>>& ambient,
		const std::vector<Ref<Texture2D>>& diffuse,
		const std::vector<Ref<Texture2D>>& specular,
		const std::vector<Ref<Texture2D>>& normal
	)
		: mAmbient(ambient)
		, mDiffuse(diffuse)
		, mSpecular(specular)
		, mNormal(normal)
	{}

	PBRMaterial::PBRMaterial(Ref<Texture2D> ambient, Ref<Texture2D> diffuse, Ref<Texture2D> specular, Ref<Texture2D> normal)
		: mAmbient({ ambient })
		, mDiffuse({ diffuse })
		, mSpecular({ specular })
		, mNormal({ normal })
	{}

	PBRMaterial::~PBRMaterial()
	{}

	int PBRMaterial::GetID() const
	{
		return static_cast<int>(MaterialID::PBR);
	}

	void PBRMaterial::LoadGLUniforms(Ref<OpenGLShader> shader)
	{
		Material::LoadGLUniforms(shader);

		int texture_unit = 0;
		for (int i = 0; i < mAmbient.size(); ++i)
		{
			mAmbient[i]->Bind(texture_unit);
			shader->UploadUniform("u_material.texture_am"/* + std::to_string(i)*/, texture_unit++);
		}
		for (int i = 0; i < mDiffuse.size(); ++i)
		{
			mDiffuse[i]->Bind(texture_unit);
			shader->UploadUniform("u_material.texture_df"/* + std::to_string(i)*/, texture_unit++);
		}
		for (int i = 0; i < mSpecular.size(); ++i)
		{
			mSpecular[i]->Bind(texture_unit);
			shader->UploadUniform("u_material.texture_sp"/* + std::to_string(i)*/, texture_unit++);
		}
		for (int i = 0; i < mNormal.size(); ++i)
		{
			mNormal[i]->Bind(texture_unit);
			shader->UploadUniform("u_material.texture_nl"/* + std::to_string(i)*/, texture_unit++);
		}
	}
}