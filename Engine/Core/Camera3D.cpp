#include "EnginePch.h"
#include "Camera3D.h"
#include "Util/Matrix.h"
#include "GameObject/GameObject.h"

namespace Engine
{

/// Camera3D

	Camera3D::Camera3D(const Vec3& position)
		: mPosition(position)
		, mView()
		, mProjection(Matrix::Projection())
	{
		mAngles.pitch = 52.0f;
		mAngles.yaw   = 0.0f;
		mAngles.roll  = 0.0f;
		UpdateViewProjection();
	}

	Camera3D::~Camera3D()
	{}

	void Camera3D::OnUpdate(const double& delta)
	{
		UpdateViewProjection();
	}

	void Camera3D::OnEvent(Event& event)
	{
		if (event.mType == Event::Type::Resized)
		{
			mProjection = Matrix::Projection(70.0f, static_cast<double>(event.mSizeEvent.width) / static_cast<double>(event.mSizeEvent.height));
		}
	}

	float Camera3D::GetPitch() const
	{
		return mAngles.pitch;
	}

	float Camera3D::GetYaw() const
	{
		return mAngles.yaw;
	}

	float Camera3D::GetRoll() const
	{
		return mAngles.roll;
	}

	const Vec3& Camera3D::GetPosition() const
	{
		return mPosition;
	}

	const Mat4& Camera3D::GetView() const
	{
		return mView;
	}

	const Mat4& Camera3D::GetProjection() const
	{
		return mProjection;
	}

	const Mat4& Camera3D::GetViewProjection() const
	{
		return mViewProjection;
	}

	void Camera3D::UpdateViewProjection()
	{
		mView			= Matrix::View(*this);
		mViewProjection = mProjection * mView;
	}

	void Camera3D::CalculatePitch()
	{
		if (Input::IsMouseButtonPressed(ENGINE_MOUSE_BUTTON_RIGHT))
		{
			mAngles.pitch -= Input::GetMouseOffset().y * 0.05f;

			if (mAngles.pitch > 89.f)
				mAngles.pitch = 89.f;
			else if (mAngles.pitch < 0.f)
				mAngles.pitch = 0.f;
		}
	}

	void Camera3D::ClampAngles()
	{
		if (mAngles.yaw < 0.0f)
		{
			mAngles.yaw += 360.f;
		}
		else if (mAngles.yaw > 360.0f)
		{
			mAngles.yaw -= 360.f;
		}
		if (mAngles.pitch < -89.0f)
		{
			mAngles.pitch = -89.0f;
		}
		else if (mAngles.pitch > 89.0f)
		{
			mAngles.pitch = 89.0f;
		}
	}

/// Camera3DLocked 

	Camera3DLocked::Camera3DLocked(const GameObject& target, float distance)
		: Camera3D(Vec3())
		, mTarget(target)
		, mDistance(distance)
		, mAngleAroundTarget(0.0f)
	{}

	Camera3DLocked::~Camera3DLocked()
	{
	}

	void Camera3DLocked::OnUpdate(const double& delta)
	{
		Camera3D::OnUpdate(delta);

		CalculateZoom();
		CalculatePitch();
		CalculateAngleAroundPlayer();
		CalculateCameraPosition();
		mAngles.yaw = 180 - (mTarget.GetTransform().GetRotation().y + mAngleAroundTarget);
	}

	void Camera3DLocked::OnEvent(Event& event)
	{
		Camera3D::OnEvent(event);

		if (event.mType == Event::Type::MouseScrolled)
		{
			mDistance -= event.mMouseScrolledEvent.y;
		}
	}

	float Camera3DLocked::CalculateHorizontalDistance()
	{
		return mDistance * cos(glm::radians(mAngles.pitch));
	}
	
	float Camera3DLocked::CalculateVerticalDistance()
	{
		return mDistance * sin(glm::radians(mAngles.pitch));
	}
	
	void Camera3DLocked::CalculateCameraPosition()
	{
		auto& playerPosition = mTarget.GetTransform().GetPosition();
		float horizontal = CalculateHorizontalDistance();
		
		float theta = mTarget.GetTransform().GetRotation().y + mAngleAroundTarget;
		
		mPosition.x = playerPosition.x - horizontal * sin(glm::radians(theta));
		mPosition.z = playerPosition.z - horizontal * cos(glm::radians(theta));
		
		float vertical = CalculateVerticalDistance();
		mPosition.y = playerPosition.y + vertical;
	}

	void Camera3DLocked::CalculateZoom()
	{
		if (mDistance < 0.5)
			mDistance = 0.5;
	}

	void Camera3DLocked::CalculateAngleAroundPlayer()
	{
		if (Input::IsMouseButtonPressed(ENGINE_MOUSE_BUTTON_LEFT))
		{
			mAngleAroundTarget += Input::GetMouseOffset().x * 0.05f;
		}
		if (mAngleAroundTarget != 0 && Input::IsKeyPressed(ENGINE_KEY_E) || Input::IsKeyPressed(ENGINE_KEY_Q))
		{
			mAngleAroundTarget = 0;
		}
	}
}