#include "EnginePch.h"
#include "PointLight.h"

namespace Engine
{
	PointLight::PointLight(
		const Vec3& position,
		const Attenuation& attenuation,
		const Color& color,
		const float& ambient,
		const float& diffuse,
		const float& specular
	)
		: Light(color, ambient, diffuse, specular)
		, m_position(position)
		, m_attenuation(attenuation)
	{
	}

	void PointLight::loadGLUniforms(Ref<OpenGLShader> shader)
	{
		Light::loadGLUniforms(shader);

		shader->uploadUniform("u_light.position",  m_position);
		shader->uploadUniform("u_light.constant",  m_attenuation.constant);
		shader->uploadUniform("u_light.linear",	   m_attenuation.linear);
		shader->uploadUniform("u_light.quadratic", m_attenuation.quadratic);
	}
}