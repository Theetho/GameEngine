#pragma once

#include "GameObject/GameObject.h"
#include "Renderer/Rendering/Renderable.h"
#include "Model/Mesh.h"

namespace Engine
{
	class Cube : public GameObject3D, public Renderable
	{
	public:
		Cube(float scale = 1.0f);
		Cube(const Vec3& scale);
		~Cube();

		void OnUpdate(const double& delta) override;
		void LoadMesh(const std::string& filename);
		inline Mesh& GetMesh()
		{
			return mMesh;
		}
	private:
		Mesh mMesh;
		void Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const override;
		
		inline void OnUiSelected() override
		{
			GameObject3D::OnUiSelected();
			ImGui::Separator();
		}
	};
}

