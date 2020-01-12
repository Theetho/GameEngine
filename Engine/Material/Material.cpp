#include "EnginePch.h"
#include "Material.h"
#include "Renderer/Rendering/Renderer.h"
#include "Renderer/Rendering/RendererAPI.h"
#include "API/OpenGL/OpenGLShader.h"

namespace Engine
{
	void Material::Load(Ref<Shader> shader)
	{
		switch (Renderer::GetAPI())
		{
		case API::OpenGL:
			LoadGLUniforms(std::dynamic_pointer_cast<OpenGLShader>(shader));
		default:
			break;
		}
	}

	void Material::LoadGLUniforms(Ref<OpenGLShader> shader)
	{
		shader->Bind();
		shader->UploadUniform("u_material.id", this->GetID());
	}


}