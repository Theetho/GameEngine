#pragma once

#include "GameObject/GameObject.h"
#include "GameObject/Transform.h"
#include "Core/Event.h"
#include "Util/Matrix.h"

namespace Engine
{
	class Camera3D : public GameObject3D
	{
	public:
		Camera3D(const Vec3& position);
		~Camera3D();

		static float Near, Far, AspectRatio, Fov;
		static float Sensitivity;

		inline float GetPitch() const
		{
			return mTransform.GetRotation().x;
		}
		inline float GetYaw() const
		{
			return mTransform.GetRotation().y;
		}
		inline float GetRoll() const
		{
			return mTransform.GetRotation().z;
		}
		inline const Mat4& GetViewMatrix() const
		{
			return Matrix::View(this);
		}
		inline const Mat4& GetProjectionMatrix() const
		{
			return Matrix::Projection(Fov, AspectRatio, Near, Far);
		}
		inline const Vec3 GetFrontVector() const
		{
			float rotation = glm::radians(mTransform.GetRotation().y);

			return Vec3(sin(rotation), 0.0f, cos(rotation));
		}
	
		void OnUpdate(const double& delta);
		void OnEvent(Event& event);

		void Rotate(const Vec2& offset);
		void ReverseOnUpAxis(const Vec3& position);
	private:
		void ClampAngles();

		void OnLeftPanel(SceneObject* caller = nullptr, std::string label = "", int number = -1) override
		{
			SceneObject::OnLeftPanel(this, "Camera", number);
		}
	};
}

