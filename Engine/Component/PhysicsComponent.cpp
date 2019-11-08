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
		, m_groundLevel(0.25f)
		, m_jump()
		, m_percentage(1.0f, 1.0f)
	{
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
		if (!m_jump.isJumping && position.y > m_groundLevel)
		{
			float height = position.y - (m_percentage.gravity * s_force.gravity * delta);
			position.y = height < m_groundLevel ? m_groundLevel : height;
		}
		else if (m_jump.isJumping)
		{
			position.y   += m_jump.jumpStrengh * delta;
			m_jump.delta += delta;
			if (m_jump.delta >= m_jump.jumpDuration)
			{
				m_jump.isJumping = false;
				m_jump.delta = 0;
			}
		}

		m_groundLevel = -100000;
	}
}