#include "EnginePch.h"
#include "CollisionSystem.h"
#include "GameObject/GameObject.h"
#include "Component/PhysicsComponent.h"

#define Epsilon 0.05f

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
		for (auto iterator : m_moveableColliders)
		{
			float groundLevel(-10000.0f);
			bool isOver = false;

			Collider* collider = iterator.first;

			collider->getOwner().isColliding(false);

			// Check for collisions with the other moveable colliders
			auto moveableIterator = m_moveableColliders.end();
			while ((--moveableIterator)->first != collider)
			{
				Collider* moveableCollider = moveableIterator->first;

				moveableCollider->getOwner().isColliding(false);
				
				// Check if this collider is on top of the other
				// We use an epsilon because float comparisons
				// are not accurate otherwise
				if (
					(fabs(collider->getMin().y - moveableCollider->getMax().y) < Epsilon)
					&& isOnTop(collider, moveableCollider)
				)
				{
					isOver = true;
					// If the ground level is lower than the max y of
					// the other collider, we update it
					if (groundLevel < moveableCollider->getMax().y + collider->getCenter().y - collider->getMin().y)
						groundLevel = moveableCollider->getMax().y + collider->getCenter().y - collider->getMin().y;
				}
				if (collide(iterator, *moveableIterator))
				{
					// If it is over it, it doesn't count as a collision
					if (!isOver)
						collider->getOwner().isColliding(true);
					moveableCollider->getOwner().isColliding(true);
				}
				isOver = false;
			}
			// Same for static colliders
			for (auto staticIterator : m_staticColliders)
			{
				Collider* staticCollider = staticIterator.first;

				staticCollider->getOwner().isColliding(false);
				
				if (
					(fabs(collider->getMin().y - staticCollider->getMax().y) < Epsilon)
					&& isOnTop(collider, staticCollider)
				)
				{
					isOver = true;
					if (groundLevel < staticCollider->getMax().y + collider->getCenter().y - collider->getMin().y)
						groundLevel = staticCollider->getMax().y + collider->getCenter().y - collider->getMin().y;
				}
				if (collide(iterator, staticIterator))
				{
					if (!isOver)
						collider->getOwner().isColliding(true);
					staticCollider->getOwner().isColliding(true);
				}
				isOver = false;
			}

			// Then update the collider's owner ground level so it
			// "collides" properly with the ground
			auto physics = collider->getOwner().GetComponent<PhysicsComponent>();

			if (physics)
				physics->setGroundLevel(groundLevel);
		}
	}

	bool CollisionSystem::isOnTop(
		Collider* c1,
		const Collider* c2
	)
	{
		return (c1->getMin().x <= c2->getMax().x && c1->getMax().x >= c2->getMin().x) &&
			   (c1->getMin().z <= c2->getMax().z && c1->getMax().z >= c2->getMin().z);
	}

	bool CollisionSystem::collide(
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
			return false;
		}
	}

	bool CollisionSystem::collide(
		const BoxCollider* b1,
		const BoxCollider* b2
	)
	{	
		return (b1->getMin().x <= b2->getMax().x && b1->getMax().x >= b2->getMin().x) &&
			   (b1->getMin().y <= b2->getMax().y && b1->getMax().y >= b2->getMin().y) &&
			   (b1->getMin().z <= b2->getMax().z && b1->getMax().z >= b2->getMin().z);
	}

	bool CollisionSystem::collide(
		const SphereCollider* s1,
		const SphereCollider* s2
	)
	{
		float distance = glm::distance(s1->getCenter(), s2->getCenter());
		return distance <= (s1->getRadius() + s2->getRadius());
	}

	bool CollisionSystem::collide(
		const PointCollider* p1,
		const PointCollider* p2
	)
	{
		return p1->getCenter() == p2->getCenter();
	}

	bool CollisionSystem::collide(
		const BoxCollider* b,
		const SphereCollider* s
	)
	{
			float x = std::max(b->getMin().x, std::min(s->getCenter().x, b->getMax().x));
			float y = std::max(b->getMin().y, std::min(s->getCenter().y, b->getMax().y));
			float z = std::max(b->getMin().z, std::min(s->getCenter().z, b->getMax().z));

			float distance = glm::distance(Vec3(x, y, z), s->getCenter());

			return distance <= s->getRadius();
	}

	bool CollisionSystem::collide(
		const SphereCollider* s,
		const BoxCollider* b
	)
	{
		return collide(b, s);
	}

	bool CollisionSystem::collide(
		const BoxCollider* b,
		const PointCollider* p
	)
	{
			return (p->getCenter().x >= b->getMin().x && p->getCenter().x <= b->getMax().x) &&
				   (p->getCenter().y >= b->getMin().y && p->getCenter().y <= b->getMax().y) &&
				   (p->getCenter().z >= b->getMin().z && p->getCenter().z <= b->getMax().z);
	}

	bool CollisionSystem::collide(
		const PointCollider* p,
		const BoxCollider* b
	)
	{
		return collide(b, p);
	}

	bool CollisionSystem::collide(
		const SphereCollider* s,
		const PointCollider* p
	)
	{
			float distance = glm::distance(s->getCenter(), p->getCenter());
			return distance <= s->getRadius();
	}

	bool CollisionSystem::collide(
		const PointCollider* p,
		const SphereCollider* s
	)
	{
		return collide(s, p);
	}
};