#include "EnginePch.h"
#include "PointLight.h"
#include "API/OpenGL/OpenGLShader.h"

namespace Engine
{
	PointLight::PointLight(const Vec3& position, const Attenuation& attenuation, const Color& color)
		: Light(color)
		, mPosition(position)
		, mAttenuation(attenuation)
	{}

	PointLight::~PointLight()
	{}

	int PointLight::GetID() const
	{
		return static_cast<int>(LightID::Point);
	}

	PointLight::Attenuation& PointLight::GetAttenuation()
	{
		return mAttenuation;
	}

	const Vec3& PointLight::GetPosition() const
	{
		return mPosition;
	}

	const PointLight::Attenuation& PointLight::GetAttenuation() const
	{
		return mAttenuation;
	}

	void PointLight::SetPosition(const Vec3& position)
	{
		mPosition = position;
	}

	void PointLight::LoadGLUniforms(Ref<OpenGLShader> shader, unsigned int index)
	{
		Light::LoadGLUniforms(shader, index);

		shader->UploadUniform("u_lights[" + std::to_string(index) + "].position",  mPosition);
		shader->UploadUniform("u_lights[" + std::to_string(index) + "].constant",  mAttenuation.constant);
		shader->UploadUniform("u_lights[" + std::to_string(index) + "].linear",	   mAttenuation.linear);
		shader->UploadUniform("u_lights[" + std::to_string(index) + "].quadratic", mAttenuation.quadratic);
	}
}