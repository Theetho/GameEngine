#include "EnginePch.h"
#include "Camera3D.h"
#include "Core/Event.h"
#include "Core/Input.h"
#include "Core/Application.h"

namespace Engine
{
	const float Camera3D::MAX_PITCH = 89.0f;
	const float Camera3D::MAX_YAW = 360.0f;
	const float Camera3D::MAX_ROLL = 360.0f;

	Camera3D::Camera3D(const Vec3& position)
		: mPosition(position)
		, mPitch(0)
		, mYaw(0)
		, mRoll(0)
		, mProjectionMatrix()
		, mViewMatrix()
	{
		mProjectionMatrix = Matrix::Projection(mFov, mAspectRatio, mNear, mFar);
		mViewMatrix = Matrix::View(this);
	}
	
	Camera3D::~Camera3D()
	{}
	
	void Camera3D::OnUpdate(const double& delta)
	{
		auto offset = Input::GetMouseOffset();
		if (offset.x || offset.y)
			Rotate(offset);
	}
	
	void Camera3D::OnEvent(Event& event)
	{
		if (event.mType == Event::Type::Resized)
		{
			mAspectRatio = static_cast<double>(event.mSizeEvent.width) / static_cast<double>(event.mSizeEvent.height);
			mProjectionMatrix = Matrix::Projection(mFov, mAspectRatio, mNear, mFar);
		}
	}

	void Camera3D::ReverseOnUpAxis(const Vec3& position)
	{
		float distance = mPosition.y - position.y;
		mPosition.y -= (2.0f * distance);
		mPitch *= -1.0f;

		UpdateViewMatrix();
	}

	void Camera3D::Rotate(const Vec2& offset)
	{
		mPitch -= (offset.y * mSensitivity.pitch);
		ClampPitch();
		mYaw   -= (offset.x * mSensitivity.yaw);
		ClampYaw();

		UpdateViewMatrix();
	}
}
