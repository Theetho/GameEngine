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

	void SpotLight::loadGLUniforms(Ref<OpenGLShader> shader)
	{
		PointLight::loadGLUniforms(shader);

		shader->uploadUniform("u_light.cutOff", glm::cos(glm::radians(m_cutOff)));
		shader->uploadUniform("u_light.direction", m_direction);
	}
}