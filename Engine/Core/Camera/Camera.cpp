#include "EnginePch.h"
#include "Camera.h"
#include "Core/Input.h"

namespace Engine
{
	Camera::Camera()
		: Camera3D(Vec3())
	{
		mMovement.position.SetTarget(mPosition);
		mMovement.target.SetTarget(mTarget);

		mSensitivity.pitch = 0.3f;
		mSensitivity.yaw = 0.3f;
		mSensitivity.roll = 0.3f;
	}
	Camera::~Camera()
	{}
	void Camera::OnUpdate(const double& delta)
	{
		CalculatePitch(delta);
		CalculateAngleAroundPlayer(delta);
		CalculateDistance(delta);
		CalculateTarget();
		CalculateCameraPosition();
		mYaw = 360.0f - mAngleAroundTarget;
		ClampYaw();
		UpdateViewMatrix();
	}

	void Camera::OnEvent(Event& event)
	{
		Camera3D::OnEvent(event);

		// Zoom in/out on scroll.
		if (event.mType == Event::MouseScrolled)
		{
			static const float ZOOM_FACTOR = 0.1f;
			float distance_change = std::max((float)mDistanceAroundTarget * ZOOM_FACTOR, 0.5f) * event.mMouseScrolledEvent.y;
			mDistanceAroundTarget.IncreaseTarget(-distance_change);
			// If the distance to the target is too low
			if (mDistanceAroundTarget.GetTarget() <= 0.0f)
			{
				mDistanceAroundTarget.SetTarget(0.1f);
				//// It changes the target using the forward vector.
				//// This allows the user to zoom in without limitation,
				//// but the lower the distance is, the slower the zoom in will be.
			/*	Vec3 forward = glm::normalize(mTarget - mPosition);
				mMovement.target.SetTarget((Vec3)mMovement.target + forward * 0.5f);*/
			}
		}
	}

	void Camera::CalculateCameraPosition()
	{
		float horizontal_distance = CalculateHorizontalDistance();
		float vertical_distance = CalculateVerticalDistance();

		mPosition.x = mTarget.x + (float)(horizontal_distance * std::sin(glm::radians((float)mAngleAroundTarget)));
		mPosition.y = mTarget.y + vertical_distance;
		mPosition.z = mTarget.z + (float)(horizontal_distance * std::cos(glm::radians((float)mAngleAroundTarget)));
	}

	void Camera::CalculatePitch(const double& delta)
	{
		if (Input::IsMouseButtonPressed(ENGINE_MOUSE_BUTTON_MIDDLE) &&
			!Input::IsKeyPressed(ENGINE_KEY_LEFT_SHIFT))
		{
			float pitch_change = Input::GetMouseOffset().y * mSensitivity.pitch;
			mSmoothPitch.IncreaseTarget(-pitch_change);
			ClampPitch();
		}
		mSmoothPitch.Update(delta);
		mPitch = (float)mSmoothPitch;
	}

	void Camera::CalculateAngleAroundPlayer(const double& delta)
	{
		if (Input::IsMouseButtonPressed(ENGINE_MOUSE_BUTTON_MIDDLE) &&
			!Input::IsKeyPressed(ENGINE_KEY_LEFT_SHIFT))
		{
			float angle_change = Input::GetMouseOffset().x * mSensitivity.yaw;
			mAngleAroundTarget.IncreaseTarget(angle_change);
		}
		mAngleAroundTarget.Update(delta);
	}

	void Camera::CalculateDistance(const double& delta)
	{
		mDistanceAroundTarget.Update(delta);
		mMovement.position.Update(Vec3(delta));
		mMovement.target.Update(Vec3(delta));
	}

	void Camera::CalculateTarget()
	{
		// Change the translation speed depending on the distance to the target
		// and ensure it is not to low.
		float speed = std::max((float)mDistanceAroundTarget / 500.f, 0.0005f);

		Vec3 forward = glm::normalize(mTarget - mPosition);
		auto right = glm::cross(forward, { 0, 1, 0 });
		auto up = glm::cross(forward, right);

		if (Input::IsMouseButtonPressed(ENGINE_MOUSE_BUTTON_MIDDLE) &&
			Input::IsKeyPressed(ENGINE_KEY_LEFT_SHIFT))
		{
			auto movement = (right * Input::GetMouseOffset().x + up * Input::GetMouseOffset().y) * speed;
			mMovement.position.IncreaseTarget(movement);
			mMovement.target.IncreaseTarget(movement);
		}

		// Update position and target smoothly.
		mPosition = mMovement.position;
		mTarget   = mMovement.target;
	}
}