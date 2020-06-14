#pragma once

#include "GameObject/GameObject.h"
#include "Model/Model.h"

namespace Engine
{
	class Cube : public GameObject3D, public Model, public SceneObject
	{
	public:
		Cube(float scale = 1.0f);
		Cube(const Vec3& scale);
		~Cube();

	private:
		void Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const override;
		inline void OnLeftPanel(SceneObject* caller = nullptr, std::string label = "", int number = -1) override
		{
			SceneObject::OnLeftPanel(this, "Cube", number);
		}

		inline void OnRightPanel() override
		{
			GameObject3D::OnRightPanel();
			ImGui::Separator();
			Model::OnRightPanel();
		}
	};
}

