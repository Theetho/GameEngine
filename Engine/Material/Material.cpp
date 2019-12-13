#include "EnginePch.h"
#include "Material.h"
#include "Renderer/Rendering/Renderer.h"

namespace Engine
{
	void Material::load(
		const Ref<Shader> shader
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

	void Material::loadGLUniforms(
		Ref<OpenGLShader> shader
	)
	{
		shader->bind();
		shader->uploadUniform("u_material.id", this->getID());
	}


}