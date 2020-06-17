#include "EnginePch.h"
#include "DirectionalLight.h"
#include "API/OpenGL/Shader.h"

namespace Engine
{
	DirectionalLight::DirectionalLight(const Vec3& direction, const Color& color)
		: Light(color)
		, mDirection(direction)
	{}

	DirectionalLight::~DirectionalLight()
	{}

	int DirectionalLight::GetID() const
	{
		return static_cast<int>(LightID::Directional);
	}

	const Vec3& DirectionalLight::GetDirection() const
	{
		return mDirection;
	}

	void DirectionalLight::SetDirection(const Vec3& direction)
	{
		mDirection = direction;
	}

	void DirectionalLight::LoadGLUniforms(Ref<OpenGL::Shader> shader, unsigned int index)
	{
		Light::LoadGLUniforms(shader, index);

		shader->UploadUniform("uLights[" + std::to_string(index) + "].direction", mDirection);
	}
	void DirectionalLight::OnLeftPanel(SceneObject* caller, std::string label)
	{
		SceneObject::OnLeftPanel(this, "Directional light");
	}
	void DirectionalLight::OnRightPanel()
	{
		Light::OnRightPanel();
		ImGui::Separator();
		ImGui::Text("Direction");
		ImGui::DragFloat3(ApplyID(""), (float*)&mDirection, 0.1f, -1.0f, 1.0f);
	}
}