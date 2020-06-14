#pragma once

#include "GameObject/GameObject.h"
#include "Renderer/Rendering/Renderable.h"

namespace Engine
{
	class VertexArray;
	class FrameBuffer;
	class Renderer;
	class Texture2D;

	class Water : public GameObject3D, public Renderable
	{
	public:
		Water(const Vec3& position, const Vec2& dimensions);
		~Water();

		void OnUpdate(const double& delta) override;

		Ref<FrameBuffer> GetRefractionBuffer() const;
		Ref<FrameBuffer> GetReflectionBuffer() const;
		const Vec3&		 GetPosition() const;
	private:
		friend class Renderer;
		Ref<VertexArray> mVertexArray;
		Ref<FrameBuffer> mRefraction;
		Ref<FrameBuffer> mReflection;
		Ref<Texture2D>	 mDUDVMap;
		Ref<Texture2D>	 mNormalMap;
		float			 mWaveMovement;
		float			 mWaveSpeed;

		void CreateTile();
		void Prepare(Camera3D& camera, Ref<Engine::FrameBuffer> binded_framebuffer = nullptr);
		void Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const override;

		virtual void OnLeftPanel(SceneObject* caller = nullptr, std::string label = "", int number = -1) override
		{
			SceneObject::OnLeftPanel(this, "Water", number);
		}

		inline void OnRightPanel() override
		{
			GameObject3D::OnRightPanel();
			ImGui::Separator();
			ImGui::Text("Wave speed");
			ImGui::DragFloat("", &mWaveSpeed, 0.005f, 0.0f, 1.0f);
		}
	};
}

