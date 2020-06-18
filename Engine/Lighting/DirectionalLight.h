#pragma once

#include "Light.h"

namespace Engine
{
	class DirectionalLight : public Light
	{
	public:
		DirectionalLight(const Vec3& direction, const Color& color = Color::White);
		~DirectionalLight();

		virtual int GetID() const override;
		const Vec3& GetDirection() const;

		void SetDirection(const Vec3& direction);
	private:
		Vec3 mDirection;

		void LoadGLUniforms(Ref<OpenGL::Shader> shader, unsigned int index) override;
		inline void OnUiSelected() override
		{
			Light::OnUiSelected();
			ImGui::Separator();
			ImGui::Text("Direction");
			ImGui::DragFloat3(ApplyID("##Direction"), (float*)&mDirection, 0.1f, -1.0f, 1.0f);
		}
	};
}