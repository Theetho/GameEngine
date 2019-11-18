#include "EnginePch.h"
#include "DirectionalLight.h"

namespace Engine
{
	DirectionalLight::DirectionalLight(
		const Vec3&  direction, 
		const Color& color
	)
		: Light(color)
		, m_direction(direction)
	{
	}

	void DirectionalLight::loadGLUniforms(
		Ref<OpenGLShader> shader,
		const unsigned int& index
	)
	{
		Light::loadGLUniforms(shader, index);

		shader->uploadUniform("u_lights[" + std::to_string(index) + "].direction", m_direction);
	}
}