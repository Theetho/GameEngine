#include "EnginePch.h"
#include "PointLight.h"
#include "API/OpenGL/Shader.h"

namespace Engine
{
	PointLight::PointLight(const Vec3& position, const Attenuation& attenuation, const Color& color)
		: Light(color)
		, mPosition(position)
		, mAttenuation(attenuation)
	{}

	PointLight::~PointLight()
	{}

	int PointLight::GetID() const
	{
		return static_cast<int>(LightID::Point);
	}

	PointLight::Attenuation& PointLight::GetAttenuation()
	{
		return mAttenuation;
	}

	const Vec3& PointLight::GetPosition() const
	{
		return mPosition;
	}

	const PointLight::Attenuation& PointLight::GetAttenuation() const
	{
		return mAttenuation;
	}

	void PointLight::SetPosition(const Vec3& position)
	{
		mPosition = position;
	}

	void PointLight::LoadGLUniforms(Ref<OpenGL::Shader> shader, unsigned int index)
	{
		Light::LoadGLUniforms(shader, index);

		shader->UploadUniform("uLights[" + std::to_string(index) + "].position",  mPosition);
		shader->UploadUniform("uLights[" + std::to_string(index) + "].constant",  mAttenuation.constant);
		shader->UploadUniform("uLights[" + std::to_string(index) + "].linear",	   mAttenuation.linear);
		shader->UploadUniform("uLights[" + std::to_string(index) + "].quadratic", mAttenuation.quadratic);
	}
	void PointLight::OnLeftPanel(SceneObject* caller, std::string label, int number)
	{
		SceneObject::OnLeftPanel(this, "Point light", number);
	}
	void PointLight::OnRightPanel()
	{
		Light::OnRightPanel();
		ImGui::Separator();
		ImGui::Text("Attenuation");
		ImGui::SliderFloat("Quadratic", &mAttenuation.quadratic, 0.0f, 10.0f);
		ImGui::SliderFloat("Linear", &mAttenuation.linear, 0.0f, 10.0f);
		ImGui::SliderFloat("Constant", &mAttenuation.constant, 0.0f, 10.0f);
		ImGui::Separator();
		ImGui::Text("Position");
		ImGui::DragFloat3("", (float*)&mPosition);
	}
}