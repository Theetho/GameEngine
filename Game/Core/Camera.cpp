#include "pch.h"
#include "Camera.h"
#include "Component/Movement.h"

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
	calculateAngleAroundPlayer();

	float horizontal = calculateHorizontalDistance();
	float vertical   = calculateVerticalDistance();

	m_position.x = m_target.getTransform().getPosition().x - horizontal * sin(glm::radians(m_angle.yaw));
	m_position.z = m_target.getTransform().getPosition().z + horizontal * cos(glm::radians(m_angle.yaw));
	m_position.y = m_target.getTransform().getPosition().y + vertical;

	updateTargetAxis();
}

void Camera::calculateAngleAroundPlayer()
{
	if (Input::isMouseButtonPressed(ENGINE_MOUSE_BUTTON_LEFT))
	{
		m_angle.yaw -= Input::getMouseOffset().x * 0.05f;
		if (m_angle.yaw < 0.0f)
		{
			m_angle.yaw += 360.f;
		}
		else if (m_angle.yaw > 360.0f)
		{
			m_angle.yaw -= 360.f;
		}
	}
}

void Camera::updateTargetAxis()
{
	auto movement = m_target.GetComponent<Movement>();

	if (!movement)
		return;

	Vec3 axis;

	if (m_angle.yaw < 45.f || m_angle.yaw >= 315.f)
	{
		axis = Vec3(0.0f, 0.0f, -1.0f);
	}
	else if (m_angle.yaw < 135.f)
	{
		axis = Vec3(1.0f, 0.0f, 0.0f);
	}
	else if (m_angle.yaw < 225.f)
	{
		axis = Vec3(0.0f, 0.0f, 1.0f);
	}
	else if (m_angle.yaw < 315.f)
	{
		axis = Vec3(-1.0f, 0.0f, 0.0f);
	}

	movement->setForwardAxis(axis);
}
