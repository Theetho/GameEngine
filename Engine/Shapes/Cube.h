#pragma once

#include "GameObject/GameObject.h"
#include "Model/Model.h"

namespace Engine
{
	class Cube : public GameObject3D, public Model
	{
	public:
		Cube(float scale = 1.0f);
		Cube(const Vec3& scale);
		~Cube();

	private:
		void Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const override;
		
		inline void OnUiSelected() override
		{
			GameObject3D::OnUiSelected();
			ImGui::Separator();
			Model::OnUiRender();
		}
	};
}

