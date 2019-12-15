#include "EnginePch.h"
#include "MovementComponent.h"
#include "Core/Log.h"
#include "GameObject/GameObject.h"
#include "Core/Input.h"
#include "Component/PhysicsComponent.h"

namespace Engine
{
	MovementComponent::MovementComponent(
		GameObject& owner
	)
		: Component(owner)
		, m_transform(owner.getTransform())
		, m_speed()
		, m_movement()
		, m_distance()
	{
	}

	MovementComponent::~MovementComponent()
	{
	}

	void MovementComponent::onUpdate(
		const double& delta
	)
	{
		if (m_owner.isColliding())
		{
			m_transform.getPosition() -= Vec3(m_movement.direction.x, 0.f, m_movement.direction.z);
			m_speed.reset();
		}

		m_movement.reset();

		float friction = 0.0f;
		
		auto physics = m_owner.GetComponent<PhysicsComponent>();

		if (physics)
			friction = physics->getFriction();

		if (Input::isKeyPressed(ENGINE_KEY_W))
		{
			if (!Input::isKeyPressed(ENGINE_KEY_S))
			{
				m_transform.getRotation().y = 180.f;
				m_speed.forward = m_speed.velocity;
				m_movement.forward = true;
			}
		}
		else if (Input::isKeyPressed(ENGINE_KEY_S))
		{
			m_speed.forward = -m_speed.velocity;
			m_transform.getRotation().y = 0.f;
			m_movement.forward = true;
		}

		if (Input::isKeyPressed(ENGINE_KEY_A))
		{
			if (!Input::isKeyPressed(ENGINE_KEY_D))
			{
				m_speed.strafe = -m_speed.velocity;
				m_transform.getRotation().y = -90.f;
				m_movement.strafe = true;
			}
		}
		else if (Input::isKeyPressed(ENGINE_KEY_D))
		{
			m_speed.strafe = m_speed.velocity;
			m_transform.getRotation().y = 90.f;
			m_movement.strafe = true;
		}

		/*if (Input::isKeyPressed(ENGINE_KEY_Q))
		{
			m_transform.getRotation().y += m_speed.rotation * delta;
		}
		if (Input::isKeyPressed(ENGINE_KEY_E))
		{
			m_transform.getRotation().y -= m_speed.rotation * delta;
		}*/

		clapSpeed(m_speed.forward, friction, m_movement.forward);
		clapSpeed(m_speed.strafe, friction, m_movement.strafe);

		// Move the GameObject along two axis only : 
		// forward and sideways

		m_distance.forward = m_speed.forward * delta;
		m_distance.strafe = m_speed.strafe * delta;

		m_movement.direction.x =
			m_distance.forward * sin(glm::radians(/*180 - */m_transform.getRotation().y))
			- m_distance.strafe * cos(glm::radians(/*180 - */m_transform.getRotation().y));

		m_movement.direction.z =
			m_distance.forward * cos(glm::radians(/*180 - */m_transform.getRotation().y))
			+ m_distance.strafe * sin(glm::radians(/*180 - */m_transform.getRotation().y));

		m_transform.getPosition() += Vec3(m_movement.direction.x, 0.f, m_movement.direction.z);

		m_transform.updateModel();
	}

	void MovementComponent::clapSpeed(
		float& speed,
		const float& friction,
		const bool& moving
	)
	{
		if (speed > 0.0f)
		{
			if (speed > m_speed.max)
			{
				speed = m_speed.max;
			}
			else if (!moving)
			{
				speed -= friction;
				if (speed < 0.0f)
					speed = 0.0f;
			}
		}
		else if (speed < 0.0f)
		{
			if (speed < - m_speed.max)
			{
				speed = - m_speed.max;
			}
			else if (!moving)
			{
				speed += friction;
				if (speed > 0.0f)
					speed = 0.0f;
			}
		}
	}
}