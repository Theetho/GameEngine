#include "EnginePch.h"
#include "CameraController.h"
#include "Core/Input.h"

namespace Engine
{
	CameraController::CameraController()
		: Entity()
		, m_speed(2.0f)
		, m_rotationSpeed(150.0f)
		, m_forwardSpeed(0.0f)
		, m_strafeSpeed(0.0f)
	{
	}

	CameraController::~CameraController()
	{
	}

	void CameraController::onUpdate(
		const double& delta
	)
	{
		move(delta);
	}

	void CameraController::move(const double& delta)
	{
		// Update the CameraController's position
		m_forwardSpeed = 0;
		if (Input::isKeyPressed(ENGINE_KEY_W))
			m_forwardSpeed += m_speed;
		if (Input::isKeyPressed(ENGINE_KEY_S))
			m_forwardSpeed -= m_speed;

		m_strafeSpeed = 0;
		if (Input::isKeyPressed(ENGINE_KEY_A))
			m_strafeSpeed -= m_speed;
		if (Input::isKeyPressed(ENGINE_KEY_D))
			m_strafeSpeed += m_speed;

		if (Input::isKeyPressed(ENGINE_KEY_SPACE))
			m_transform.getPosition().y += m_speed * delta;

		if (Input::isKeyPressed(ENGINE_KEY_Q))
			m_transform.getRotation().z -= m_rotationSpeed * delta;
		if (Input::isKeyPressed(ENGINE_KEY_E))
			m_transform.getRotation().z += m_rotationSpeed * delta;

		// Move the CameraController along two axis only : 
		// forward and sideways
		float distance_forward = m_forwardSpeed * delta;
		float distance_sideway = m_strafeSpeed * delta;

		float dx =
			distance_forward * sin(glm::radians(180 - m_transform.getRotation().z))
			- distance_sideway * cos(glm::radians(180 - m_transform.getRotation().z));

		float dz =
			distance_forward * cos(glm::radians(180 - m_transform.getRotation().z))
			+ distance_sideway * sin(glm::radians(180 - m_transform.getRotation().z));

		m_transform.getPosition() += Vec3(dx, 0.f, dz);
		m_transform.updateModel();
	}
}