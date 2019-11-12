#include "EnginePch.h"
#include "PhysicsComponent.h"
#include "GameObject/GameObject.h"
#include "Core/Log.h"

namespace Engine
{
	const PhysicsComponent::Force PhysicsComponent::s_force(5.0f, 0.3f);

	PhysicsComponent::PhysicsComponent(
		GameObject& owner
	)
		: Component(owner)
		, m_transform(owner.getTransform())
		, m_groundLevel(0.0f)
		, m_jump()
		, m_percentage(1.0f, 1.0f)
	{
		m_jump.isJumping = true;
	}

	PhysicsComponent::~PhysicsComponent()
	{
	}

	void PhysicsComponent::onUpdate(
		const double& delta
	)
	{
		Vec3& position = m_transform.getPosition();
		
		// Gravity
		if (!m_jump.isJumping && (position.y > m_groundLevel))
		{
			position.y -= m_percentage.gravity * s_force.gravity * (float)delta;
		}
		// Jump
		else if (m_jump.isJumping)
		{
			position.y   += m_jump.jumpStrengh * delta;
			m_jump.delta += delta;
			if (m_jump.delta >= m_jump.jumpDuration)
			{
				m_jump.isJumping = false;
				m_jump.isFalling = true;
				m_jump.delta = 0;
			}
		}
		// Only goes here when the object hits the ground
		else if (m_jump.isFalling)
		{
			m_jump.isFalling = false;
		}

		m_groundLevel = -1000.0f;
	}
}