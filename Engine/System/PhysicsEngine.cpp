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
		resolveCollisions();
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

	void PhysicsEngine::resolveCollisions()
	{
		std::sort(m_colliders.begin(), m_colliders.end(),
			[](const Collider* c1, const Collider* c2)
			{
				return c1->getRigidBody();
			}
		);

		size_t i = 0;
		while (i < m_colliders.size() && m_colliders[i]->getRigidBody())
		{
			auto collider = m_colliders[i];

			for (size_t j = i + 1; j < m_colliders.size(); ++j)
			{
				Collision collision = detectCollision(collider, m_colliders[j]);
			}
			++i;
		}
	}

	Collision PhysicsEngine::detectCollision(
		Collider* mainCollider,
		Collider* otherCollider
	) const
	{
		const Vec3& center       = mainCollider->getCenter();
		const Vec3& size         = (mainCollider->getMax() - mainCollider->getMin()) / 2.0f;
		const Vec3& size_squared = size * size;

		/*for (size_t i = 0; i < otherCollider->getVertices().size(); ++i)
		{

		}*/

		return Collision(false, 0, mainCollider, otherCollider);
	}
}