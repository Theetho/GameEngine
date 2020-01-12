#include "EnginePch.h"
#include "Light.h"
#include "Renderer/Rendering/Renderer.h"
#include "Renderer/Rendering/RendererAPI.h"
#include "API/OpenGL/OpenGLShader.h"


namespace Engine
{
	Light::Light(const Color& color)
		: mColor(color)
	{}

	Light::~Light()
	{}

	void Light::Load(Ref<Shader> shader, unsigned int index)
	{
		switch (Renderer::GetAPI())
		{
		case API::OpenGL:
			LoadGLUniforms(std::dynamic_pointer_cast<OpenGLShader>(shader), index);
		default:
			break;
		}
	}

	const Color& Light::GetColor() const
	{
		return mColor;
	}

	void Light::SetColor(const Color& color)
	{
		mColor = color;
	}

	void Light::LoadGLUniforms(Ref<OpenGLShader> shader, unsigned int index)
	{
		shader->Bind();
		shader->UploadUniform("u_lights[" + std::to_string(index) + "].id",	   this->GetID());
		shader->UploadUniform("u_lights[" + std::to_string(index) + "].color", Vec3(mColor));
	}
}