#include "pch.h"
#include "CameraLocked.h"
#include "Component/Movement.h"

using namespace Engine;

CameraLocked::CameraLocked(
	const GameObject& target,
	float distance
)
	: Camera3DLocked(target, distance)
{
	mAngles.yaw = 180.0f;
}

CameraLocked::~CameraLocked()
{}

void CameraLocked::OnUpdate(const double& delta)
{
	Camera3D::OnUpdate(delta);

	CalculateZoom();
	CalculatePitch();
	CalculateAngleAroundPlayer();

	float horizontal = CalculateHorizontalDistance();
	float vertical   = CalculateVerticalDistance();

	mPosition.x = mTarget.GetTransform().GetPosition().x - horizontal * sin(glm::radians(mAngles.yaw));
	mPosition.z = mTarget.GetTransform().GetPosition().z + horizontal * cos(glm::radians(mAngles.yaw));
	mPosition.y = mTarget.GetTransform().GetPosition().y + vertical;

	UpdateTargetAxis();
}

void CameraLocked::CalculateAngleAroundPlayer()
{
	if (Input::IsMouseButtonPressed(ENGINE_MOUSE_BUTTON_LEFT))
	{
		mAngles.yaw -= Input::GetMouseOffset().x * 0.05f;
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

void CameraLocked::UpdateTargetAxis()
{
	auto movement = mTarget.GetComponent<Movement>();

	if (!movement)
		return;

	Vec3 axis;

	if (mAngles.yaw < 45.f || mAngles.yaw >= 315.f)
	{
		axis = Vec3(0.0f, 0.0f, -1.0f);
	}
	else if (mAngles.yaw < 135.f)
	{
		axis = Vec3(1.0f, 0.0f, 0.0f);
	}
	else if (mAngles.yaw < 225.f)
	{
		axis = Vec3(0.0f, 0.0f, 1.0f);
	}
	else if (mAngles.yaw < 315.f)
	{
		axis = Vec3(-1.0f, 0.0f, 0.0f);
	}

	movement->SetForwardAxis(axis);
}
