#include "EnginePch.h"
#include "SpotLight.h"

namespace Engine
{
	SpotLight::SpotLight(
		const Vec3& position,
		const Vec3& direction,
		const float& cutOff,
		const Attenuation& attenuation,
		const Color& color,
		const float& ambient,
		const float& diffuse,
		const float& specular
	)
		: PointLight(position, attenuation, color, ambient, diffuse, specular)
		, m_direction(direction)
		, m_cutOff(cutOff)
	{
	}

	void SpotLight::loadGLUniforms(
		Ref<OpenGLShader> shader,
		const unsigned int& index
	)
	{
		PointLight::loadGLUniforms(shader, index);

		shader->uploadUniform("u_lights[" + std::to_string(index) + "].cutOff"   , glm::cos(glm::radians(m_cutOff)));
		shader->uploadUniform("u_lights[" + std::to_string(index) + "].direction", m_direction);
	}
}