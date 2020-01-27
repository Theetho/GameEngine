#include "EnginePch.h"
#include "Material.h"
#include "Renderer/Rendering/Renderer.h"
#include "Renderer/Rendering/RendererAPI.h"
#include "API/OpenGL/Shader.h"

namespace Engine
{
	void Material::Load(Ref<Shader> shader)
	{
		switch (Renderer::GetAPI())
		{
		case API::OpenGL:
			LoadGLUniforms(std::dynamic_pointer_cast<OpenGL::Shader>(shader));
		default:
			break;
		}
	}

	void Material::LoadGLUniforms(Ref<OpenGL::Shader> shader)
	{
		shader->Bind();
		shader->UploadUniform("uMaterial.id", this->GetID());
	}


}