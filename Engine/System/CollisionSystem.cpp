#include "EnginePch.h"
#include "CollisionSystem.h"
#include "GameObject/GameObject.h"
#include "Component/MovementComponent.h"
#include "Util/Benchmark.h"

static bool display = true;

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
		checkForOneCollision();
	}

	void CollisionSystem::checkForOneCollision()
	{
#define check_collision(x) if (x) continue; 

		bool collision = false;

		std::vector<BoxCollider*>    movingBoxes;
		std::vector<SphereCollider*> movingSpheres;
		std::vector<PointCollider*>  movingPoints;

		std::vector<BoxCollider*>    staticBoxes;
		std::vector<SphereCollider*> staticSpheres;
		std::vector<PointCollider*>  staticPoints;

		// Separate moving objects from static objects;
		for (auto it : m_boxes)
		{
			if (it->getOwner().isMoving() || it->getOwner().isJumping())
			{
				movingBoxes.push_back(it);
			}
			else
			{
				staticBoxes.push_back(it);
			}
		}
		for (auto it : m_spheres)
		{
			if (it->getOwner().isMoving() || it->getOwner().isJumping())
			{
				movingSpheres.push_back(it);
			}
			else
			{
				staticSpheres.push_back(it);
			}
		}
		for (auto it : m_points)
		{
			if (it->getOwner().isMoving() || it->getOwner().isJumping())
			{
				movingPoints.push_back(it);
			}
			else
			{
				staticPoints.push_back(it);
			}
		}

		// Moving box
		for (int i = 0; i < movingBoxes.size(); ++i)
		{
			collision = false;

			movingBoxes[i]->getOwner().isColliding(false);
			for (int j = i + 1; j < movingBoxes.size(); ++i)
			{
				movingBoxes[j]->getOwner().isColliding(false);
				if (collide(movingBoxes[i], movingBoxes[j]))
				{
					movingBoxes[i]->getOwner().isColliding(true);
					movingBoxes[j]->getOwner().isColliding(true);
					collision = true;
					break;
				}
			}
			check_collision(collision)
			
			for (auto& it : movingSpheres)
			{
				it->getOwner().isColliding(false);
				if (collide(movingBoxes[i], it))
				{
					movingBoxes[i]->getOwner().isColliding(true);
					it->getOwner().isColliding(true);
					collision = true;
					break;
				}
			}
			check_collision(collision)
			
			for (auto& it : movingPoints)
			{
				it->getOwner().isColliding(false);
				if (collide(movingBoxes[i], it))
				{
					movingBoxes[i]->getOwner().isColliding(true);
					it->getOwner().isColliding(true);
					collision = true;
					break;
				}
			}
			check_collision(collision)
			
			for (auto& it : staticBoxes)
			{
				it->getOwner().isColliding(false);
				if (collide(movingBoxes[i], it))
				{
					movingBoxes[i]->getOwner().isColliding(true);
					it->getOwner().isColliding(true);
					collision = true;
					break;
				}
			}
			check_collision(collision)
			
			for (auto& it : staticSpheres)
			{
				it->getOwner().isColliding(false);
				if (collide(movingBoxes[i], it))
				{
					movingBoxes[i]->getOwner().isColliding(true);
					it->getOwner().isColliding(true);
					collision = true;
					break;
				}
			}
			check_collision(collision)
			
			for (auto& it : staticPoints)
			{
				it->getOwner().isColliding(false);
				if (collide(movingBoxes[i], it))
				{
					movingBoxes[i]->getOwner().isColliding(true);
					it->getOwner().isColliding(true);
					collision = true;
					break;
				}
			}
		}

		// Moving spheres
		for (int i = 0; i < movingSpheres.size(); ++i)
		{
			collision = false;

			movingSpheres[i]->getOwner().isColliding(false);
			for (int j = i + 1; j < movingSpheres.size(); ++i)
			{
				movingSpheres[j]->getOwner().isColliding(false);
				if (collide(movingSpheres[i], movingSpheres[j]))
				{
					movingSpheres[i]->getOwner().isColliding(true);
					movingSpheres[j]->getOwner().isColliding(true);
					collision = true;
					break;
				}
			}
			check_collision(collision)

			for (auto& it : movingPoints)
				{
					it->getOwner().isColliding(false);
					if (collide(movingSpheres[i], it))
					{
						movingSpheres[i]->getOwner().isColliding(true);
						it->getOwner().isColliding(true);
						collision = true;
						break;
					}
				}
			check_collision(collision)

			for (auto& it : staticBoxes)
				{
					it->getOwner().isColliding(false);
					if (collide(movingSpheres[i], it))
					{
						movingSpheres[i]->getOwner().isColliding(true);
						it->getOwner().isColliding(true);
						collision = true;
						break;
					}
				}
			check_collision(collision)

			for (auto& it : staticSpheres)
				{
					it->getOwner().isColliding(false);
					if (collide(movingSpheres[i], it))
					{
						movingSpheres[i]->getOwner().isColliding(true);
						it->getOwner().isColliding(true);
						collision = true;
						break;
					}
				}
			check_collision(collision)

			for (auto& it : staticPoints)
				{
					it->getOwner().isColliding(false);
					if (collide(movingSpheres[i], it))
					{
						movingSpheres[i]->getOwner().isColliding(true);
						it->getOwner().isColliding(true);
						collision = true;
						break;
					}
				}
		}

		// Moving points
		for (int i = 0; i < movingPoints.size(); ++i)
		{
			collision = false;

			movingPoints[i]->getOwner().isColliding(false);
			for (int j = i + 1; j < movingPoints.size(); ++i)
			{
				movingPoints[j]->getOwner().isColliding(false);
				if (collide(movingPoints[i], movingPoints[j]))
				{
					movingPoints[i]->getOwner().isColliding(true);
					movingPoints[j]->getOwner().isColliding(true);
					collision = true;
					break;
				}
			}
			check_collision(collision)

			for (auto& it : staticBoxes)
				{
					it->getOwner().isColliding(false);
					if (collide(movingPoints[i], it))
					{
						movingPoints[i]->getOwner().isColliding(true);
						it->getOwner().isColliding(true);
						collision = true;
						break;
					}
				}
			check_collision(collision)

			for (auto& it : staticSpheres)
				{
					it->getOwner().isColliding(false);
					if (collide(movingPoints[i], it))
					{
						movingPoints[i]->getOwner().isColliding(true);
						it->getOwner().isColliding(true);
						collision = true;
						break;
					}
				}
			check_collision(collision)

			for (auto& it : staticPoints)
				{
					it->getOwner().isColliding(false);
					if (collide(movingPoints[i], it))
					{
						movingPoints[i]->getOwner().isColliding(true);
						it->getOwner().isColliding(true);
						collision = true;
						break;
					}
				}
		}
	}

	void CollisionSystem::checkForAllCollision()
	{
		std::vector<BoxCollider*>    movingBoxes;
		std::vector<SphereCollider*> movingSpheres;
		std::vector<PointCollider*>  movingPoints;

		std::vector<BoxCollider*>    staticBoxes;
		std::vector<SphereCollider*> staticSpheres;
		std::vector<PointCollider*>  staticPoints;

		// Separate moving objects from static objects;
		for (auto it : m_boxes)
		{
			if (it->getOwner().isMoving() || it->getOwner().isJumping())
			{
				movingBoxes.push_back(it);
			}
			else
			{
				staticBoxes.push_back(it);
			}
		}
		for (auto it : m_spheres)
		{
			if (it->getOwner().isMoving() || it->getOwner().isJumping())
			{
				movingSpheres.push_back(it);
			}
			else
			{
				staticSpheres.push_back(it);
			}
		}
		for (auto it : m_points)
		{
			if (it->getOwner().isMoving() || it->getOwner().isJumping())
			{
				movingPoints.push_back(it);
			}
			else
			{
				staticPoints.push_back(it);
			}
		}

		// Moving box
		for (int i = 0; i < movingBoxes.size(); ++i)
		{
			movingBoxes[i]->getOwner().isColliding(false);
			for (int j = i + 1; j < movingBoxes.size(); ++i)
			{
				movingBoxes[j]->getOwner().isColliding(false);
				if (collide(movingBoxes[i], movingBoxes[j]))
				{
					movingBoxes[i]->getOwner().isColliding(true);
					movingBoxes[j]->getOwner().isColliding(true);
				}
			}
			
			for (auto& it : movingSpheres)
			{
				it->getOwner().isColliding(false);
				if (collide(movingBoxes[i], it))
				{
					movingBoxes[i]->getOwner().isColliding(true);
					it->getOwner().isColliding(true);
				}
			}

			for (auto& it : movingPoints)
			{
				it->getOwner().isColliding(false);
				if (collide(movingBoxes[i], it))
				{
					movingBoxes[i]->getOwner().isColliding(true);
					it->getOwner().isColliding(true);
				}
			}

			for (auto& it : staticBoxes)
			{
				it->getOwner().isColliding(false);
				if (collide(movingBoxes[i], it))
				{
					movingBoxes[i]->getOwner().isColliding(true);
					it->getOwner().isColliding(true);
				}
			}

			for (auto& it : staticSpheres)
			{
				it->getOwner().isColliding(false);
				if (collide(movingBoxes[i], it))
				{
					movingBoxes[i]->getOwner().isColliding(true);
					it->getOwner().isColliding(true);
				}
			}

			for (auto& it : staticPoints)
			{
				it->getOwner().isColliding(false);
				if (collide(movingBoxes[i], it))
				{
					movingBoxes[i]->getOwner().isColliding(true);
					it->getOwner().isColliding(true);
				}
			}
		}

		// Moving spheres
		for (int i = 0; i < movingSpheres.size(); ++i)
		{
			movingSpheres[i]->getOwner().isColliding(false);
			for (int j = i + 1; j < movingSpheres.size(); ++i)
			{
				movingSpheres[j]->getOwner().isColliding(false);
				if (collide(movingSpheres[i], movingSpheres[j]))
				{
					movingSpheres[i]->getOwner().isColliding(true);
					movingSpheres[j]->getOwner().isColliding(true);
				}
			}

			for (auto& it : movingPoints)
			{
				it->getOwner().isColliding(false);
				if (collide(movingSpheres[i], it))
				{
					movingSpheres[i]->getOwner().isColliding(true);
					it->getOwner().isColliding(true);
				}
			}

			for (auto& it : staticBoxes)
			{
				it->getOwner().isColliding(false);
				if (collide(movingSpheres[i], it))
				{
					movingSpheres[i]->getOwner().isColliding(true);
					it->getOwner().isColliding(true);
				}
			}

			for (auto& it : staticSpheres)
			{
				it->getOwner().isColliding(false);
				if (collide(movingSpheres[i], it))
				{
					movingSpheres[i]->getOwner().isColliding(true);
					it->getOwner().isColliding(true);
				}
			}

			for (auto& it : staticPoints)
			{
				it->getOwner().isColliding(false);
				if (collide(movingSpheres[i], it))
				{
					movingSpheres[i]->getOwner().isColliding(true);
					it->getOwner().isColliding(true);
				}
			}
		}

		// Moving points
		for (int i = 0; i < movingPoints.size(); ++i)
		{
			movingPoints[i]->getOwner().isColliding(false);
			for (int j = i + 1; j < movingPoints.size(); ++i)
			{
				movingPoints[j]->getOwner().isColliding(false);
				if (collide(movingPoints[i], movingPoints[j]))
				{
					movingPoints[i]->getOwner().isColliding(true);
					movingPoints[j]->getOwner().isColliding(true);
				}
			}

			for (auto& it : staticBoxes)
			{
				it->getOwner().isColliding(false);
				if (collide(movingPoints[i], it))
				{
					movingPoints[i]->getOwner().isColliding(true);
					it->getOwner().isColliding(true);
				}
			}

			for (auto& it : staticSpheres)
			{
				it->getOwner().isColliding(false);
				if (collide(movingPoints[i], it))
				{
					movingPoints[i]->getOwner().isColliding(true);
					it->getOwner().isColliding(true);
				}
			}

			for (auto& it : staticPoints)
			{
				it->getOwner().isColliding(false);
				if (collide(movingPoints[i], it))
				{
					movingPoints[i]->getOwner().isColliding(true);
					it->getOwner().isColliding(true);
				}
			}
		}
	}

	bool CollisionSystem::collide(
		const BoxCollider* b1,
		const BoxCollider* b2
	)
	{
		return (b1->getMin().x < b2->getMax().x && b1->getMax().x > b2->getMin().x) &&
			   (b1->getMin().y < b2->getMax().y && b1->getMax().y > b2->getMin().y) &&
			   (b1->getMin().z < b2->getMax().z && b1->getMax().z > b2->getMin().z);
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