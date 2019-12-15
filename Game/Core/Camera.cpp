#include "pch.h"
#include "Camera.h"

using namespace Engine;

Camera::Camera(
	const GameObject& target,
	float distance
)
	: Camera3DLocked(target, distance)
{
	m_angle.yaw = 180.0f;
}

Camera::~Camera()
{
}

void Camera::onUpdate(
	const double& delta
)
{
	Camera3D::onUpdate(delta);

	calculateZoom();
	calculatePitch();

	float horizontal = calculateHorizontalDistance();
	float vertical   = calculateVerticalDistance();

	m_position.x = m_target.getTransform().getPosition().x;
	m_position.z = m_target.getTransform().getPosition().z - horizontal;
	m_position.y = m_target.getTransform().getPosition().y + vertical;
}
