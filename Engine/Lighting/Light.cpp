#include "EnginePch.h"
#include "Light.h"
#include "Renderer/Rendering/Renderer.h"
#include "Renderer/Rendering/RendererAPI.h"
#include "API/OpenGL/Shader.h"
#include "Core/Application.h"
#include "Core/Scene/Scene.h"

namespace Engine
{
	Light::Light(const Color& color)
		: SceneObject(false)
		, mColor(color)
		, mActive(true)
	{}

	Light::~Light()
	{}

	void Light::Load(Ref<Shader> shader, unsigned int index)
	{
		switch (Renderer::GetAPI())
		{
		case API::OpenGL:
			LoadGLUniforms(std::dynamic_pointer_cast<OpenGL::Shader>(shader), index);
		default:
			break;
		}
	}

	void Light::Unload(Ref<Shader> shader, unsigned int index)
	{
		switch (Renderer::GetAPI())
		{
			case API::OpenGL:
				UnloadGLUniforms(std::dynamic_pointer_cast<OpenGL::Shader>(shader), index);
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

	void Light::LoadGLUniforms(Ref<OpenGL::Shader> shader, unsigned int index)
	{
		shader->Bind();
		shader->UploadUniform("uLights[" + std::to_string(index) + "].minDiffuseFactor", mMinDiffuseFactor);
		shader->UploadUniform("uLights[" + std::to_string(index) + "].id"   , this->GetID());
		shader->UploadUniform("uLights[" + std::to_string(index) + "].color", Vec3(mColor));
	}

	void Light::UnloadGLUniforms(Ref<OpenGL::Shader> shader, unsigned int index)
	{
		shader->Bind();
		shader->UploadUniform("uLights[" + std::to_string(index) + "].id", 0);
		shader->UploadUniform("uLights[" + std::to_string(index) + "].color", 0);
	}
}