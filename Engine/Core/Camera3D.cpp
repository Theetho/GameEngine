#include "EnginePch.h"
#include "Camera3D.h"
#include "Input.h"
#include "Util/Matrix.h"
#include "GameObject/CameraController.h"

namespace Engine
{

	Camera3D::Camera3D(
		const Vec3& position
	)
		: m_position(position)
		, m_view()
		, m_projection(Matrix::projection())
		, m_VP()
		, m_pitch(20.0f)
		, m_yaw(-20.0f)
		, m_speed(2.0f)
		, m_mouseSpeed(0.02f)
		, m_rotationSpeed(150.0f)
		, m_forwardSpeed(0.0f)
		, m_strafeSpeed(0.0f)
		, m_controller(nullptr)
	{
		updateVP();
	}

	Camera3D::~Camera3D()
	{
	}

	void Camera3D::onUpdate(const double& delta)
	{
		if (m_controller)
		{
			if (m_controller->isJumping())
			{
				m_position.x = m_controller->getTransform().getPosition().x + m_controller->getOffset().x;
				m_position.z = m_controller->getTransform().getPosition().z + m_controller->getOffset().z;
			}
			else
				m_position = m_controller->getTransform().getPosition() + m_controller->getOffset();
		}
		else
		{
			// Update the camera position
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
				m_position.y += m_speed * delta;
			if (Input::isKeyPressed(ENGINE_KEY_LEFT_SHIFT))
				m_position.y -= m_speed * delta;

			if (Input::isKeyPressed(ENGINE_KEY_Q))
				m_yaw -= m_rotationSpeed * delta;
			if (Input::isKeyPressed(ENGINE_KEY_E))
				m_yaw += m_rotationSpeed * delta;

			// Move the camera along fixed axis (independant
			// from the pitch and yaw)
			float distance_forward = m_forwardSpeed * delta;
			float distance_sideway = m_strafeSpeed * delta;

			float dx =
				distance_forward * sin(glm::radians(180 - m_yaw))
				- distance_sideway * cos(glm::radians(180 - m_yaw));

			float dz =
				distance_forward * cos(glm::radians(180 - m_yaw))
				+ distance_sideway * sin(glm::radians(180 - m_yaw));

			m_position += Vec3(dx, 0.f, dz);

			// Update the pitch and yaw
			auto mouse_rel = Input::getMouseOffset();
			m_yaw -= mouse_rel.x * m_mouseSpeed;
			m_pitch -= mouse_rel.y * m_mouseSpeed;

		}
		
		updateVP();
	}

	void Camera3D::onEvent(Event& event)
	{
		if (event.type == Event::Type::Resized)
		{
			m_projection = Matrix::projection(
				static_cast<double>(event.sizeEvent.width)
			  / static_cast<double>(event.sizeEvent.height)
			);
		}
	}

	void Camera3D::updateVP()
	{
		m_view = Matrix::view(*this);
		m_VP   = m_projection * m_view;
	}
}