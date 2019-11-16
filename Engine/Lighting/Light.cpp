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
		Ref<Shader> shader,
		const unsigned int& index
	)
	{
		switch (Renderer::getAPI())
		{
		case API::OpenGL:
			loadGLUniforms(std::dynamic_pointer_cast<OpenGLShader>(shader), index);
		default:
			break;
		}
	}
	void Light::loadGLUniforms(
		Ref<OpenGLShader> shader,
		const unsigned int& index
	)
	{
		shader->bind();
		shader->uploadUniform("u_lights[" + std::to_string(index) + "].id",		  this->getID());
		shader->uploadUniform("u_lights[" + std::to_string(index) + "].ambient",  m_ambient);
		shader->uploadUniform("u_lights[" + std::to_string(index) + "].diffuse",  m_diffuse);
		shader->uploadUniform("u_lights[" + std::to_string(index) + "].specular", m_specular);
		shader->uploadUniform("u_lights[" + std::to_string(index) + "].color",    Vec3(m_color));
	}
}