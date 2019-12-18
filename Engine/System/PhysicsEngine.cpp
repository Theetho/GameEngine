#include "..\..\2DDevelop\PhysicsEngine.h"
#include "EnginePch.h"
#include "PhysicsEngine.h"

namespace Engine
{
	PhysicsEngine* PhysicsEngine::s_instance = new PhysicsEngine();

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
		//std::sort(m_colliders.begin(), m_colliders.end(),
		//	[](const Collider* c1, const Collider* c2)
		//	{
		//		return c1->getRigidBody();
		//	}
		//);

		for (size_t i = 0; i < m_colliders.size(); ++i)
		{
			auto collider = m_colliders[i];

			for (size_t j = i + 1; j < m_colliders.size(); ++j)
			{
				if (&collider->getOwner() == &m_colliders[j]->getOwner())
					continue;

				Collision collision = detectCollision(collider, m_colliders[j]);

				if (collision.doesCollide())
				{
					collider->getOwner().onCollision(collision);
				}
			}
		}
	}

	Collision PhysicsEngine::detectCollision(
		const Collider* mainCollider,
		const Collider* otherCollider
	) const
	{
		Vec3 mainDimension  = (mainCollider->getMax() - mainCollider->getMin());
		Vec3 otherDimension = (otherCollider->getMax() - otherCollider->getMin());

		Vec3 distanceVector = mainCollider->getCenter() - otherCollider->getCenter();
		float distance = glm::length(distanceVector);

		Vec3 collisionDirection = glm::normalize(distanceVector);

		Vec3 mainSize =  collisionDirection * mainDimension;
		Vec3 otherSize = collisionDirection * otherDimension;

		float mainDistance = glm::length(mainSize);
		float otherDistance = glm::length(otherSize);
		float minimumDistance = mainDistance + otherDistance;

		return Collision(
			distance < minimumDistance, 
			std::abs(distanceVector.y - (mainSize.y + otherSize.y)),
			mainCollider, otherCollider
		);
	}
}