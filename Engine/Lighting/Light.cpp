#include "EnginePch.h"
#include "Light.h"
#include "Renderer/Rendering/Renderer.h"

namespace Engine
{
	Light::Light(
		const Color& color
	)
		: m_color(color)
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
		shader->uploadUniform("u_lights[" + std::to_string(index) + "].id",	   this->getID());
		shader->uploadUniform("u_lights[" + std::to_string(index) + "].color", Vec3(m_color));
	}
}