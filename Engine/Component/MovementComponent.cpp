#include "EnginePch.h"
#include "MovementComponent.h"
#include "GameObject/GameObject.h"
#include "Core/Input.h"
#include "Component/PhysicsComponent.h"

namespace Engine
{
	MovementComponent::MovementComponent(
		GameObject* owner
	)
		: Component(owner)
		, m_transform(&owner->getTransform())
		, m_speed()
		, m_movement()
	{
	}

	MovementComponent::~MovementComponent()
	{
	}

	void MovementComponent::onUpdate(
		const double& delta
	)
	{
		m_movement.reset();
	
		auto physics = m_owner->getComponent<PhysicsComponent>();

		float friction = physics->getFriction();

		// Update the GameObject's position
		if (Input::isKeyPressed(ENGINE_KEY_W))
		{
			m_speed.forward += m_speed.velocity;
			m_movement.forward = true;
		}
		if (Input::isKeyPressed(ENGINE_KEY_S))
		{
			m_speed.forward -= m_speed.velocity;
			m_movement.forward = true;
		}

		if (Input::isKeyPressed(ENGINE_KEY_A))
		{
			m_speed.strafe -= m_speed.velocity;
			m_movement.strafe = true;
		}
		if (Input::isKeyPressed(ENGINE_KEY_D))
		{
			m_speed.strafe += m_speed.velocity;
			m_movement.strafe = true;
		}

		if (Input::isKeyPressed(ENGINE_KEY_Q))
			m_transform->getRotation().z -= m_speed.rotation * delta;
		if (Input::isKeyPressed(ENGINE_KEY_E))
			m_transform->getRotation().z += m_speed.rotation * delta;

		clapSpeed(m_speed.forward, friction, m_movement.forward);
		clapSpeed(m_speed.strafe, friction, m_movement.strafe);

		// Move the GameObject along two axis only : 
		// forward and sideways
		m_distance.forward  = m_speed.forward * delta;
		m_distance.strafe = m_speed.strafe * delta;
	
		m_movement.dx =
			m_distance.forward * sin(glm::radians(180 - m_transform->getRotation().z))
		  - m_distance.strafe  * cos(glm::radians(180 - m_transform->getRotation().z));

		m_movement.dz =
			m_distance.forward * cos(glm::radians(180 - m_transform->getRotation().z))
		  + m_distance.strafe  * sin(glm::radians(180 - m_transform->getRotation().z));

		m_transform->getPosition() += Vec3(m_movement.dx, 0.f, m_movement.dz);
		m_transform->updateModel();
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