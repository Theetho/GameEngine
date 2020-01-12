#include "EnginePch.h"
#include "RawMaterial.h"
#include "API/OpenGL/OpenGLShader.h"

namespace Engine
{
	RawMaterial RawMaterial::Emerald(Color(0.0215f, 0.1745f, 0.0215f), Color(0.07568f, 0.61424f, 0.07568f), Color(0.633f, 0.727811f, 0.633f), 0.6* 128);
	RawMaterial RawMaterial::Jade(Color(0.135f, 0.2225f, 0.1575f), Color(0.54f, 0.89f, 0.63f), Color(0.316228f, 0.316228f, 0.316228f), 0.1* 128);
	RawMaterial RawMaterial::Obsidian(Color(0.05375f, 0.05f, 0.06625f), Color(0.18275f, 0.17f, 0.22525f), Color(0.332741f, 0.328634f, 0.346435f), 0.3* 128);
	RawMaterial RawMaterial::Pearl(Color(0.25f, 0.20725f, 0.20725f), Color(1.0f, 0.829f, 0.829f), Color(0.296648f, 0.296648f, 0.296648f), 0.088* 128);
	RawMaterial RawMaterial::Ruby(Color(0.1745f, 0.01175f, 0.01175f), Color(0.61424f, 0.04136f, 0.04136f), Color(0.727811f, 0.626959f, 0.626959f), 0.6* 128);
	RawMaterial RawMaterial::Turquoise(Color(0.1f, 0.18725f, 0.1745f), Color(0.396f, 0.74151f, 0.69102f), Color(0.297254f, 0.30829f, 0.306678f), 0.1* 128);
	RawMaterial RawMaterial::Brass(Color(0.329412f, 0.223529f, 0.027451f), Color(0.780392f, 0.568627f, 0.113725f), Color(0.992157f, 0.941176f, 0.807843f), 0.21794872* 128);
	RawMaterial RawMaterial::Bronze(Color(0.2125f, 0.1275f, 0.054f), Color(0.714f, 0.4284f, 0.18144f), Color(0.393548f, 0.271906f, 0.166721f), 0.2* 128);
	RawMaterial RawMaterial::Chrome(Color(0.25f, 0.25f, 0.25f), Color(0.4f, 0.4f, 0.4f), Color(0.774597f, 0.774597f, 0.774597f), 0.6* 128);
	RawMaterial RawMaterial::Copper(Color(0.19125f, 0.0735f, 0.0225f), Color(0.7038f, 0.27048f, 0.0828f), Color(0.256777f, 0.137622f, 0.086014f), 0.1* 128);
	RawMaterial RawMaterial::Gold(Color(0.24725f, 0.1995f, 0.0745f), Color(0.75164f, 0.60648f, 0.22648f), Color(0.628281f, 0.555802f, 0.366065f), 0.4* 128);
	RawMaterial RawMaterial::Silver(Color(0.19225f, 0.19225f, 0.19225f), Color(0.50754f, 0.50754f, 0.50754f), Color(0.508273f, 0.508273f, 0.508273f), 0.4* 128);
	RawMaterial RawMaterial::BlackPlastic(Color(0.0f, 0.0f, 0.0f), Color(0.01f, 0.01f, 0.01f), Color(0.50f, 0.50f, 0.50f), 0.25* 128);
	RawMaterial RawMaterial::CyanPlastic(Color(0.0f, 0.1f, 0.06f), Color(0.0f, 0.50980392f, 0.50980392f), Color(0.50196078f, 0.50196078f, 0.50196078f), 0.25* 128);
	RawMaterial RawMaterial::GreenPlastic(Color(0.0f, 0.0f, 0.0f), Color(0.1f, 0.35f, 0.1f), Color(0.45f, 0.55f, 0.45f), 0.25* 128);
	RawMaterial RawMaterial::RedPlastic(Color(0.0f, 0.0f, 0.0f), Color(0.5f, 0.0f, 0.0f), Color(0.7f, 0.6f, 0.6f), 0.25* 128);
	RawMaterial RawMaterial::WhitePlastic(Color(0.0f, 0.0f, 0.0f), Color(0.55f, 0.55f, 0.55f), Color(0.70f, 0.70f, 0.70f), 0.25* 128);
	RawMaterial RawMaterial::YellowPlastic(Color(0.0f, 0.0f, 0.0f), Color(0.5f, 0.5f, 0.0f), Color(0.60f, 0.60f, 0.50f), 0.25* 128);
	RawMaterial RawMaterial::BlackRubber(Color(0.02f, 0.02f, 0.02f), Color(0.01f, 0.01f, 0.01f), Color(0.4f, 0.4f, 0.4f), 0.078125* 128);
	RawMaterial RawMaterial::CyanRubber(Color(0.0f,0.05f,0.05f), Color(0.4f, 0.5f, 0.5f), Color(0.04f, 0.7f, 0.7f), 0.078125* 128);
	RawMaterial RawMaterial::GreenRubber(Color(0.0f,0.05f,0.0f), Color(0.4f, 0.5f, 0.4f), Color(0.04f, 0.7f, 0.04f), 0.078125* 128);
	RawMaterial RawMaterial::RedRubber(Color(0.05f,0.0f,0.0f), Color(0.5f, 0.4f, 0.4f), Color(0.7f, 0.04f, 0.04f), 0.078125* 128);
	RawMaterial RawMaterial::WhiteRubber(Color(0.05f,0.05f,0.05f), Color(0.5f, 0.5f, 0.5f), Color(0.7f, 0.7f, 0.7f),0.078125* 128);
	RawMaterial RawMaterial::YellowRubber(Color(0.05f,0.05f,0.0f), Color(0.5f, 0.5f, 0.4f), Color(0.7f, 0.7f, 0.04f),0.078125* 128);
	
	
	RawMaterial::RawMaterial(
		const Color& ambient,
		const Color& diffuse,
		const Color& specular,
		float shininess
	)
		: mAmbient(ambient)
		, mDiffuse(diffuse)
		, mSpecular(specular)
		, mShininess(shininess)
	{}

	RawMaterial::~RawMaterial()
	{}

	int RawMaterial::GetID() const
	{
		return static_cast<int>(MaterialID::Raw);
	}

	void RawMaterial::LoadGLUniforms(Ref<OpenGLShader> shader)
	{
		Material::LoadGLUniforms(shader);

		shader->UploadUniform("u_material.shininess", mShininess);
		shader->UploadUniform("u_material.ambient",   Vec3(mAmbient));
		shader->UploadUniform("u_material.diffuse",   Vec3(mDiffuse));
		shader->UploadUniform("u_material.specular",  Vec3(mSpecular));
	}
}