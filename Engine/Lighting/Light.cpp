#include "EnginePch.h"
#include "Light.h"
#include "Renderer/Renderer.h"

namespace Engine
{
	Light::Light(
		const Color& color,
		const float& ambient,
		const float& diffuse,
		const float& specular
	)
		: m_color(color)
		, m_ambient	(ambient)
		, m_diffuse(diffuse)
		, m_specular(specular)
	{
	}

	void Light::load(
		Ref<Shader> shader
	)
	{
		switch (Renderer::getAPI())
		{
		case API::OpenGL:
			loadGLUniforms(std::dynamic_pointer_cast<OpenGLShader>(shader));
		default:
			break;
		}
	}
	void Light::loadGLUniforms(Ref<OpenGLShader> shader)
	{
		shader->bind();
		shader->uploadUniform("u_light.ambient",  m_ambient);
		shader->uploadUniform("u_light.diffuse",  m_diffuse);
		shader->uploadUniform("u_light.specular", m_specular);
		shader->uploadUniform("u_light.color",    Vec3(m_color));
	}
}