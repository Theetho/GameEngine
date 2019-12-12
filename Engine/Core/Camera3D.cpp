#include "EnginePch.h"
#include "Camera3D.h"
#include "Util/Matrix.h"
#include "GameObject/GameObject.h"

namespace Engine
{

/// Camera3D

	Camera3D::Camera3D(
		const Vec3& position
	)
		: m_view()
		, m_projection(Matrix::projection())
		, m_VP()
	{
		m_angle.pitch = 52.0f;
		m_angle.yaw   = 0.0f;
		m_angle.roll  = 0.0f;
		updateVP();
	}

	Camera3D::~Camera3D()
	{
	}

	void Camera3D::onUpdate(const double& delta)
	{
		updateVP();
	}

	void Camera3D::onEvent(Event& event)
	{
		if (event.type == Event::Type::Resized)
		{
			m_projection = Matrix::projection(
				70.0f,
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

/// Camera3DLocked 

	Camera3DLocked::Camera3DLocked(
		const GameObject& target,
		const float& distance
	)
		: Camera3D()
		, m_target(target)
		, m_distance(distance)
		, m_angleAroundTarget(0.0f)
	{
	}

	Camera3DLocked::~Camera3DLocked()
	{
	}

	void Camera3DLocked::onUpdate(const double& delta)
	{
		Camera3D::onUpdate(delta);

		calculateZoom();
		calculatePitch();
		calculateAngleAroundPlayer();
		calculateCameraPosition();
		m_angle.yaw = 180 - (m_target.getTransform().getRotation().y + m_angleAroundTarget);
	}

	void Camera3DLocked::onEvent(Event& event)
	{
		Camera3D::onEvent(event);

		if (event.type == Event::Type::MouseScrolled)
		{
			m_distance -= event.mouseScrolledEvent.y;
		}
	}

	float Camera3DLocked::calculateHorizontalDistance()
	{
		return m_distance * cos(glm::radians(m_angle.pitch));
	}
	inline float Camera3DLocked::calculateVerticalDistance()
	{
		return m_distance * sin(glm::radians(m_angle.pitch));
	}
	inline void Camera3DLocked::calculateCameraPosition()
	{
		auto& playerPosition = m_target.getTransform().getPosition();
		float horizontal = calculateHorizontalDistance();
		
		float theta = m_target.getTransform().getRotation().y + m_angleAroundTarget;
		
		m_position.x = playerPosition.x - horizontal * sin(glm::radians(theta));
		m_position.z = playerPosition.z - horizontal * cos(glm::radians(theta));
		
		float vertical = calculateVerticalDistance();
		m_position.y = playerPosition.y + vertical;
	}

	inline void Camera3DLocked::calculateZoom()
	{
		if (m_distance < 0.5)
			m_distance = 0.5;
	}

	void Camera3DLocked::calculateAngleAroundPlayer()
	{
		if (Input::isMouseButtonPressed(ENGINE_MOUSE_BUTTON_LEFT))
		{
			m_angleAroundTarget += Input::getMouseOffset().x * 0.05f;
		}
		if (m_angleAroundTarget != 0 && Input::isKeyPressed(ENGINE_KEY_E) || Input::isKeyPressed(ENGINE_KEY_Q))
		{
			m_angleAroundTarget = 0;
		}
	}

}