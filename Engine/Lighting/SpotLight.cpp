#include "EnginePch.h"
#include "SpotLight.h"
#include "API/OpenGL/Shader.h"

namespace Engine
{
	SpotLight::SpotLight(
		const Vec3& position,
		const Vec3& direction,
		float cut_off,
		const Attenuation& attenuation,
		const Color& color
	)
		: PointLight(position, attenuation, color)
		, mDirection(direction)
		, mCutOff(cut_off)
	{}

	SpotLight::~SpotLight()
	{}

	const Vec3& SpotLight::GetDirection() const
	{
		return mDirection;
	}

	float SpotLight::GetCutOff() const
	{
		return mCutOff;
	}

	int SpotLight::GetID() const
	{
		return static_cast<int>(LightID::Spot);
	}

	void SpotLight::LoadGLUniforms(Ref<OpenGL::Shader> shader, unsigned int index)
	{
		PointLight::LoadGLUniforms(shader, index);

		shader->UploadUniform("uLights[" + std::to_string(index) + "].cutOff"   , glm::cos(glm::radians(mCutOff)));
		shader->UploadUniform("uLights[" + std::to_string(index) + "].direction", mDirection);
	}
	void SpotLight::OnLeftPanel(SceneObject* caller, std::string label, int number)
	{
		SceneObject::OnLeftPanel(this, "Spot light", number);
	}
	void SpotLight::OnRightPanel()
	{
		PointLight::OnRightPanel();
		ImGui::Separator();
		ImGui::DragFloat("Cut off", &mCutOff, 0.1f, 0.0f, 10000.0f);
		ImGui::Separator();
		ImGui::Text("Direction");
		ImGui::DragFloat3("##35", (float*)&mDirection, 0.1f, -1.0f, 1.0f);
	}
}