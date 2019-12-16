#include "EnginePch.h"
#include "PhysicsEngine.h"

namespace Engine
{
	PhysicsEngine::PhysicsEngine()
	{
	}

	PhysicsEngine::~PhysicsEngine()
	{
	}

	void PhysicsEngine::onUpdate(
		const double& delta
	)
	{
		applyGravity(m_rigidBodies);
		handleCollision();
	}

	void PhysicsEngine::applyGravity(
		std::vector<RigidBody*>& rigidBodies
	) const
	{
		for (auto rigidBody : rigidBodies)
		{
			if (!rigidBody->m_isKinematic && rigidBody->m_useGravity)
			{
				rigidBody->m_velocity.y -= GRAVITATIONAL_ACCELERATION;
			}
		}
	}

	void PhysicsEngine::handleCollision() const
	{
		for (size_t i = 0; i < m_rigidBodies.size(); ++i)
		{
			auto rigidBody = m_rigidBodies[i];
			for (size_t j = i + 1; j < m_rigidBodies.size(); ++j)
			{

			}
		}
	}
}