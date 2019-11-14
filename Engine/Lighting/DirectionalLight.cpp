#include "EnginePch.h"
#include "DirectionalLight.h"

namespace Engine
{
	DirectionalLight::DirectionalLight(
		const Vec3&  direction, 
		const Color& color, 
		const float& ambient, 
		const float& diffuse, 
		const float& specular
	)
		: Light(color, ambient, diffuse, specular)
		, m_direction(direction)
	{
	}

	void DirectionalLight::loadGLUniforms(Ref<OpenGLShader> shader)
	{
		Light::loadGLUniforms(shader);

		shader->uploadUniform("u_light.direction", m_direction);
	}
}