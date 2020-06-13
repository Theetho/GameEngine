#include "EnginePch.h"
#include "Camera.h"
#include "Core/Event.h"
#include "Core/Input.h"
#include "Core/Application.h"

#define PITCH mTransform.GetRotation().x
#define YAW   mTransform.GetRotation().y
#define FOV_INCREMENT 3
#define MIN_FOV 70
#define MAX_FOV 110	

namespace Engine
{
	float Camera3D::Near = 0.1f;
	float Camera3D::Far = 3000.0f;
	float Camera3D::Fov = 90.0f;
	float Camera3D::AspectRatio = 16.0f / 9.0f;
	float Camera3D::Sensitivity = 0.025f;

	Camera3D::Camera3D(const Vec3& position)
		: GameObject3D()
	{
		mTransform.SetPosition(position);
	}
	Camera3D::~Camera3D()
	{
	}
	void Camera3D::OnUpdate(const double& delta)
	{
		GameObject3D::OnUpdate(delta);
		
		if (Application::Get().IsPlaying() || Input::IsMouseButtonPressed(ENGINE_MOUSE_BUTTON_2))
		{
			Rotate(Input::GetMouseOffset());
		}
	}
	void Camera3D::OnEvent(Event& event)
	{
		if (event.mType == Event::Type::Resized)
		{
			Camera3D::AspectRatio = static_cast<double>(event.mSizeEvent.width) / static_cast<double>(event.mSizeEvent.height);
		}

	}

	void Camera3D::ReverseOnUpAxis(const Vec3& position)
	{
		float position_y = mTransform.GetPosition().y;
		float distance = position_y - position.y;
		mTransform.SetPosition('y', mTransform.GetPosition().y - 2.0f * distance);
		mTransform.GetRotation().x *= -1.0f;
	}
	
	void Camera3D::Rotate(const Vec2& offset)
	{
		mTransform.SetRotation('x', PITCH - offset.y * Camera3D::Sensitivity);
		mTransform.SetRotation('y', YAW	  - offset.x * Camera3D::Sensitivity);
	
		ClampAngles();
	}

	void Camera3D::ClampAngles()
	{
		if (YAW < 0.0f)
		{
			mTransform.SetRotation('y', YAW + 360.f);
		}
		else if (YAW > 360.0f)
		{
			mTransform.SetRotation('y', YAW - 360.f);
		}

		if (PITCH > 89.f)
		{
			mTransform.SetRotation('x', 89.f);
		}
		else if (PITCH < -89.f)
		{
			mTransform.SetRotation('x', -89.f);
		}
	}
}