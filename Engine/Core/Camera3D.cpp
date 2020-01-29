#include "EnginePch.h"
#include "Camera3D.h"
#include "Event.h"
#include "Input.h"
#include "GameObject/Transform.h"

namespace Engine
{
	/// Camera3D

	const float Camera3D::Near = 0.1f, Camera3D::Far = 3000.0f;

	Camera3D::Camera3D(const Vec3& position)
		: GameObject(Transform(position, Vec3(20.0f, 40.0f, 0.0f), Vec3(1.0f)))
		, mAngles(mTransform.GetRotation().x, mTransform.GetRotation().y, mTransform.GetRotation().z)
		, mView()
		, mProjection(Matrix::Projection(70, 16.0f/9.0f, Near, Far))
	{
		AddComponent<RigidBody>(CreateRef<RigidBody>(*this));
		GetComponent<RigidBody>()->SetUseGravity(false);
		AddComponent<BoxCollider>(CreateRef<BoxCollider>(*this, position, Vec3(1.0, 1.5, 1.0)));

		UpdateViewProjection();
	}

	Camera3D::~Camera3D()
	{
	}

	void Camera3D::OnUpdate(const double& delta)
	{
		GameObject::OnUpdate(delta);

		UpdatePitch();
		ClampAngles();
		UpdateViewProjection();
	}

	void Camera3D::OnEvent(Event& event)
	{
		if (event.mType == Event::Type::Resized)
		{
			mProjection = Matrix::Projection(70.0f, static_cast<double>(event.mSizeEvent.width) / static_cast<double>(event.mSizeEvent.height));
		}
	}

	void Camera3D::ReverseOnUpAxis(const Vec3& position)
	{
		float position_y = mTransform.GetPosition().y;
		float distance   = position_y - position.y;
		mTransform.SetPosition('y', mTransform.GetPosition().y - 2.0f * distance);
		mAngles.pitch *= -1.0f;
		UpdateViewProjection();
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
		return mTransform.GetPosition();
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

	void Camera3D::SetPosition(const Vec3& position)
	{
		mTransform.SetPosition(position);
	}

	void Camera3D::UpdateViewProjection()
	{
		mView = Matrix::View(*this);
		mViewProjection = mProjection * mView;
	}

	void Camera3D::UpdatePitch()
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
	}
}