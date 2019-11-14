#include "EnginePch.h"
#include "CollisionSystem.h"
#include "GameObject/GameObject.h"
#include "Component/PhysicsComponent.h"

namespace Engine
{
	Ref<CollisionSystem> CollisionSystem::s_instance = CollisionSystem::Create();

	CollisionSystem::CollisionSystem()
	{
		ENGINE_ASSERT(!s_instance, "A collision system instance already exists");
	}

	CollisionSystem::~CollisionSystem()
	{
	}

	void CollisionSystem::onUpdate(const double& delta)
	{
		checkForMovingObjectsCollisions();
	}
		
	void CollisionSystem::checkForMovingObjectsCollisions()
	{
		// Only check the collisions for moveable objects
		for (auto iterator : m_moveableColliders)
		{
			Collider* collider = iterator.first;

			collider->getOwner().isColliding(false);
			// Check for collisions with the other moveable colliders
			auto moveableIterator = m_moveableColliders.end();
			while ((--moveableIterator)->first != collider)
			{
				Collider* moveableCollider = moveableIterator->first;

				Collision collision = collide(iterator, *moveableIterator);
				if (collision.doesCollide())
				{
					collider->getOwner().onCollision(collision);
				}
			}
			// Same with static colliders
			for (auto staticIterator : m_staticColliders)
			{
				Collider* staticCollider = staticIterator.first;
				
				Collision collision = collide(iterator, staticIterator);
				if (collision.doesCollide())
				{
					collider->getOwner().onCollision(collision);
				}
			}
		}
	}

	Collision CollisionSystem::collide(
		const std::pair<Collider*, std::type_index>& kv1,
		const std::pair<Collider*, std::type_index>& kv2
	)
	{
		if (kv1.second == typeid(BoxCollider))
		{
			if (kv2.second == typeid(BoxCollider))
			{
				return collide((BoxCollider*)kv1.first, (BoxCollider*)kv2.first);
			}
			else if (kv2.second == typeid(SphereCollider))
			{
				return collide((BoxCollider*)kv1.first, (SphereCollider*)kv2.first);
			}
			else if (kv2.second == typeid(PointCollider))
			{
				return collide((BoxCollider*)kv1.first, (PointCollider*)kv2.first);
			}
		}
		else if (kv1.second == typeid(SphereCollider))
		{
			if (kv2.second == typeid(BoxCollider))
			{
				return collide((SphereCollider*)kv1.first, (BoxCollider*)kv2.first);
			}
			else if (kv2.second == typeid(SphereCollider))
			{
				return collide((SphereCollider*)kv1.first, (SphereCollider*)kv2.first);
			}
			else if (kv2.second == typeid(PointCollider))
			{
				return collide((SphereCollider*)kv1.first, (PointCollider*)kv2.first);
			}
		}
		else if (kv1.second == typeid(PointCollider))
		{
			if (kv2.second == typeid(BoxCollider))
			{
				return collide((PointCollider*)kv1.first, (BoxCollider*)kv2.first);
			}
			else if (kv2.second == typeid(SphereCollider))
			{
				return collide((PointCollider*)kv1.first, (SphereCollider*)kv2.first);
			}
			else if (kv2.second == typeid(PointCollider))
			{
				return collide((PointCollider*)kv1.first, (PointCollider*)kv2.first);
			}
		}
		else
		{
			std::cout << "This collider is not handled by the system" << std::endl;
			return Collision(false, 0.0f, kv1.first, kv2.first);
		}
	}

	Collision CollisionSystem::collide(
		const BoxCollider* b1,
		const BoxCollider* b2
	)
	{
		return Collision(
			   (b1->getMin().x <= b2->getMax().x && b1->getMax().x >= b2->getMin().x)
			&& (b1->getMin().y <= b2->getMax().y && b1->getMax().y >= b2->getMin().y)
			&& (b1->getMin().z <= b2->getMax().z && b1->getMax().z >= b2->getMin().z)
			, std::min(std::abs(b1->getMin().y - b2->getMax().y), std::abs(b1->getMax().y - b2->getMin().y))
			, b1 , b2
		);
	}

	Collision CollisionSystem::collide(
		const SphereCollider* s1,
		const SphereCollider* s2
	)
	{
		float distance = glm::distance(s1->getCenter(), s2->getCenter());
		return Collision(
				distance <= (s1->getRadius() + s2->getRadius())
			  , distance
			  , s1, s2
		);
	}

	Collision CollisionSystem::collide(
		const PointCollider* p1,
		const PointCollider* p2
	)
	{
		return Collision(
				p1->getCenter() == p2->getCenter()
			  , glm::distance(p1->getCenter(), p2->getCenter())
			  , p1, p2
		);
	}

	Collision CollisionSystem::collide(
		const BoxCollider* b,
		const SphereCollider* s
	)
	{
			float x = std::max(b->getMin().x, std::min(s->getCenter().x, b->getMax().x));
			float y = std::max(b->getMin().y, std::min(s->getCenter().y, b->getMax().y));
			float z = std::max(b->getMin().z, std::min(s->getCenter().z, b->getMax().z));

			float distance = glm::distance(Vec3(x, y, z), s->getCenter());

			return Collision(
				distance <= s->getRadius()
			  , std::min(std::abs(s->getCenter().y - b->getMax().y), std::abs(s->getCenter().y - b->getMin().y))
			  , b, s
			);
	}

	Collision CollisionSystem::collide(
		const SphereCollider* s,
		const BoxCollider* b
	)
	{
		return collide(b, s);
	}

	Collision CollisionSystem::collide(
		const BoxCollider* b,
		const PointCollider* p
	)
	{
			return Collision(
				   (p->getCenter().x >= b->getMin().x && p->getCenter().x <= b->getMax().x)
				&& (p->getCenter().y >= b->getMin().y && p->getCenter().y <= b->getMax().y)
				&& (p->getCenter().z >= b->getMin().z && p->getCenter().z <= b->getMax().z)
				  , glm::distance(b->getCenter(), p->getCenter())
				  , b, p
			);
	}

	Collision CollisionSystem::collide(
		const PointCollider* p,
		const BoxCollider* b
	)
	{
		return collide(b, p);
	}

	Collision CollisionSystem::collide(
		const SphereCollider* s,
		const PointCollider* p
	)
	{
			float distance = glm::distance(s->getCenter(), p->getCenter());
			return Collision(
				distance <= s->getRadius()
			  , distance
			  , s, p
			);
	}

	Collision CollisionSystem::collide(
		const PointCollider* p,
		const SphereCollider* s
	)
	{
		return collide(s, p);
	}
};