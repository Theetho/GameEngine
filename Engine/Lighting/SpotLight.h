#pragma once

#include "PointLight.h"

namespace Engine
{
	
	class Color;

	class SpotLight : public PointLight
	{
	public:
		SpotLight(
			const Vec3& position,
			const Vec3& direction,
			float cut_off = 12.5f,
			const Attenuation& attenuation = Attenuation(),
			const Color& color = Color::White
		);
		~SpotLight();

		int			GetID() const override;
		float		GetCutOff() const;
		const Vec3& GetDirection() const;

		void SetDirection(const Vec3& direction)
		{
			mDirection = direction;
		}
	private:
		float mCutOff = 12.5f;
		Vec3  mDirection;

		void LoadGLUniforms(Ref<OpenGL::Shader> shader, unsigned int index) override;
		inline void OnUiSelected() override
		{
			PointLight::OnUiSelected();
			ImGui::Separator();
			ImGui::DragFloat(ApplyID("Cut off"), &mCutOff, 0.1f, 0.0f, 10000.0f);
			ImGui::Separator();
			ImGui::Text("Direction");
			ImGui::DragFloat3(ApplyID("##Direction"), (float*)&mDirection, 0.1f, -1.0f, 1.0f);
		}
	};
}

