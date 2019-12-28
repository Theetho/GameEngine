#include "EnginePch.h"
#include "SpotLight.h"

namespace Engine
{
	SpotLight::SpotLight(
		const Vec3& position,
		const Vec3& direction,
		float cut_off,
		const Attenuation& attenuation,
		const Color& color
	)
		: PointLight(position, attenuation, color)
		, mDirection(direction)
		, mCutOff(cut_off)
	{}

	SpotLight::~SpotLight()
	{}

	const Vec3& SpotLight::GetDirection() const
	{
		return mDirection;
	}

	float SpotLight::GetCutOff() const
	{
		return mCutOff;
	}

	int SpotLight::GetID() const
	{
		return static_cast<int>(LightID::Spot);
	}

	void SpotLight::LoadGLUniforms(Ref<OpenGLShader> shader, unsigned int index)
	{
		PointLight::LoadGLUniforms(shader, index);

		shader->UploadUniform("u_lights[" + std::to_string(index) + "].cutOff"   , glm::cos(glm::radians(mCutOff)));
		shader->UploadUniform("u_lights[" + std::to_string(index) + "].direction", mDirection);
	}
}