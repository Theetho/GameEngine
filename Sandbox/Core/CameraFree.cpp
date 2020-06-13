#include "pch.h"
#include "CameraFree.h"
#include "Component/Movement.h"

using namespace Engine;

CameraFree::CameraFree(const Vec3& position)
	: Camera3D(position)
{
	AddComponent<Movement3D>(CreateRef<Movement3D>(*this, true));
}

CameraFree::~CameraFree()
{
}

void CameraFree::OnUpdate(const double& delta)
{
	Camera3D::OnUpdate(delta);
	
	if (Input::IsMouseButtonPressed(ENGINE_MOUSE_BUTTON_LEFT))
	{
		mAngles.yaw -= Input::GetMouseOffset().x * 0.05f;
	}
	else if (Input::IsMouseButtonPressed(ENGINE_MOUSE_BUTTON_RIGHT))
	{
		mAngles.pitch -= Input::GetMouseOffset().y * 0.05f;
	}
}

//void CameraFree::OnCollision(const Engine::Collision& collision)
//{
//	if (collision.IsColliding)
//	{
//		auto rigid_body = GetComponent<RigidBody>();
//		rigid_body->GetTransform().SetPosition('y', collision.PenetrationDistance.y);
//	}
//}