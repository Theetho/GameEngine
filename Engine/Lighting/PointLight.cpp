#include "EnginePch.h"
#include "PointLight.h"

namespace Engine
{
	PointLight::PointLight(
		const Vec3& position,
		const Attenuation& attenuation,
		const Color& color
	)
		: Light(color)
		, m_position(position)
		, m_attenuation(attenuation)
	{
	}

	void PointLight::loadGLUniforms(
		Ref<OpenGLShader> shader,
		const unsigned int& index
	)
	{
		Light::loadGLUniforms(shader, index);

		shader->uploadUniform("u_lights[" + std::to_string(index) + "].position",  m_position);
		shader->uploadUniform("u_lights[" + std::to_string(index) + "].constant",  m_attenuation.constant);
		shader->uploadUniform("u_lights[" + std::to_string(index) + "].linear",	  m_attenuation.linear);
		shader->uploadUniform("u_lights[" + std::to_string(index) + "].quadratic", m_attenuation.quadratic);
	}
}