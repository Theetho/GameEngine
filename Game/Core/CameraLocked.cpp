#include "pch.h"
#include "CameraLocked.h"
#include "Component/Movement.h"

using namespace Engine;

CameraLocked::CameraLocked(const GameObject& target, float distance)
	: Camera3D(Vec3())
	, mTarget(target)
	, mDistance(distance)
	, mAngleAroundTarget(0.0f)
{
}

CameraLocked::~CameraLocked()
{}

void CameraLocked::OnUpdate(const double& delta)
{
	Camera3D::OnUpdate(delta);

	ClampZoom();
	UpdateAngleAroundPlayer();
	UpdatePosition();
	mAngles.yaw = 180 - (mTarget.GetTransform().GetRotation().y + mAngleAroundTarget);
}

void CameraLocked::OnEvent(Event& event)
{
	Camera3D::OnEvent(event);

	if (event.mType == Event::Type::MouseScrolled)
	{
		mDistance -= event.mMouseScrolledEvent.y;
	}
}

float CameraLocked::GetHorizontalDistance()
{
	return mDistance * cos(glm::radians(mAngles.pitch));
}

float CameraLocked::GetVerticalDistance()
{
	return mDistance * sin(glm::radians(mAngles.pitch));
}

void CameraLocked::ClampZoom()
{
	if (mDistance < 0.1)
		mDistance = 0.1;
}

void CameraLocked::UpdateAngleAroundPlayer()
{
	if (Input::IsMouseButtonPressed(ENGINE_MOUSE_BUTTON_LEFT))
	{
		mAngleAroundTarget += Input::GetMouseOffset().x * 0.05f;
	}
	if (mAngleAroundTarget != 0 && (Input::IsKeyPressed(ENGINE_KEY_E) || Input::IsKeyPressed(ENGINE_KEY_Q)))
	{
		mAngleAroundTarget = 0;
	}
}

void CameraLocked::UpdatePosition()
{
	auto& target_position = mTarget.GetTransform().GetPosition();
	
	float horizontal = GetHorizontalDistance();	
	float vertical   = GetVerticalDistance();
	
	float theta = mTarget.GetTransform().GetRotation().y + mAngleAroundTarget;
	
	mTransform.SetPosition('x', target_position.x - horizontal * sin(glm::radians(theta)));
	mTransform.SetPosition('z', target_position.z - horizontal * cos(glm::radians(theta)));
	mTransform.SetPosition('y', target_position.y + vertical);
}

//void CameraLocked::UpdateTargetAxis()
//{
//	auto movement = mTarget.GetComponent<Movement>();
//
//	if (!movement)
//		return;
//
//	Vec3 axis;
//
//	if (mAngles.yaw < 45.f || mAngles.yaw >= 315.f)
//	{
//		axis = Vec3(0.0f, 0.0f, -1.0f);
//	}
//	else if (mAngles.yaw < 135.f)
//	{
//		axis = Vec3(1.0f, 0.0f, 0.0f);
//	}
//	else if (mAngles.yaw < 225.f)
//	{
//		axis = Vec3(0.0f, 0.0f, 1.0f);
//	}
//	else if (mAngles.yaw < 315.f)
//	{
//		axis = Vec3(-1.0f, 0.0f, 0.0f);
//	}
//
//	movement->SetForwardAxis(axis);
//}