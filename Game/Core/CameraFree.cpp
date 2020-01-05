#include "pch.h"
#include "CameraFree.h"

using namespace Engine;

CameraFree::CameraFree(const Vec3& position)
	: Camera3D(position)
	, mVelocity()
{
}

CameraFree::~CameraFree()
{
}

void CameraFree::OnUpdate(const double& delta)
{
	mVelocity = Vec3();

	if (Input::IsKeyPressed(ENGINE_KEY_W))
	{
		if (!Input::IsKeyPressed(ENGINE_KEY_S))
		{
			mVelocity.x += mSpeed * delta;
		}
	}
	else if (Input::IsKeyPressed(ENGINE_KEY_S))
	{
		mVelocity.x -= mSpeed * delta;
	}

	if (Input::IsKeyPressed(ENGINE_KEY_A))
	{
		if (!Input::IsKeyPressed(ENGINE_KEY_D))
		{
			mVelocity.z -= mSpeed * delta;
		}
	}
	else if (Input::IsKeyPressed(ENGINE_KEY_D))
	{
		mVelocity.z += mSpeed * delta;
	}

	if (Input::IsKeyPressed(ENGINE_KEY_SPACE))
	{
		if (!Input::IsKeyPressed(ENGINE_KEY_LEFT_CONTROL))
		{
			mVelocity.y += mSpeed * delta;
		}
	}
	else if (Input::IsKeyPressed(ENGINE_KEY_LEFT_CONTROL))
	{
		mVelocity.y -= mSpeed * delta;
	}

	if (Input::IsMouseButtonPressed(ENGINE_MOUSE_BUTTON_LEFT))
	{
		mAngles.yaw -= Input::GetMouseOffset().x * 0.05f;
	}
	else if (Input::IsMouseButtonPressed(ENGINE_MOUSE_BUTTON_RIGHT))
	{
		mAngles.pitch -= Input::GetMouseOffset().y * 0.05f;
	}

	float dx = mVelocity.x * sin(glm::radians(180 - mAngles.yaw)) - mVelocity.z * cos(glm::radians(180 - mAngles.yaw));
	float dz = mVelocity.x * cos(glm::radians(180 - mAngles.yaw)) + mVelocity.z * sin(glm::radians(180 - mAngles.yaw));
	mPosition += Vec3(dx, mVelocity.y, dz);

	Camera3D::ClampAngles();
	Camera3D::OnUpdate(delta);
}

void CameraFree::OnEvent(Event& event)
{
	//Camera3D::OnEvent(event);
}
