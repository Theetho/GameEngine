#pragma once

#include "GameObject/GameObject.h"

namespace Engine
{
	class Event;

	class Camera3D : public GameObject
	{
	public:
		Camera3D(const Vec3& position);
		virtual ~Camera3D();

		virtual void OnUpdate(const double& delta);
		virtual void OnEvent(Event& event);
		void ReverseOnUpAxis(const Vec3& position);

		float GetPitch() const;
		float GetYaw() const;
		float GetRoll() const;
		
		const Vec3& GetPosition() const;
		const Mat4& GetView() const;
		const Mat4& GetProjection() const;
		const Mat4& GetViewProjection() const;

		void SetPosition(const Vec3& position);

		static const float Near, Far;
	protected:
		Mat4 mView;
		Mat4 mProjection;
		Mat4 mViewProjection;
		struct EulerAngle
		{
			float& pitch;
			float& yaw;
			float& roll;
			EulerAngle(float& p, float& y, float& r)
				: pitch(p), yaw(y), roll(r) {}
		};
		EulerAngle mAngles;

		void UpdateViewProjection();
		void UpdatePitch();
		void ClampAngles();
	};
}

