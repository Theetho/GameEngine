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

		float GetPitch() const;
		float GetYaw() const;
		float GetRoll() const;
		
		const Vec3& GetPosition() const;
		const Mat4& GetView() const;
		const Mat4& GetProjection() const;
		const Mat4& GetViewProjection() const;

		void SetPosition(const Vec3& position)
		{
			mPosition = position;
		}
	protected:
		Mat4 mView;
		Mat4 mProjection;
		Mat4 mViewProjection;
		Vec3 mPosition;
		struct EulerAngle
		{
			float pitch;
			float yaw;
			float roll;
		};
		EulerAngle mAngles;

		void UpdateViewProjection();
		void CalculatePitch();
		void ClampAngles();
	};

	class Camera3DLocked : public Camera3D
	{
	public:
		Camera3DLocked(const GameObject& target, float distance = 6.0f);
		virtual ~Camera3DLocked();

		virtual void OnUpdate(const double& delta) override;
		virtual void OnEvent(Event& event) override;
	protected:
		const GameObject& mTarget;

		float mDistance;
		float mAngleAroundTarget;

		virtual float CalculateHorizontalDistance();
		virtual float CalculateVerticalDistance();
		virtual void  CalculateCameraPosition();
		virtual void  CalculateZoom();
		virtual void  CalculateAngleAroundPlayer();
	};
}

