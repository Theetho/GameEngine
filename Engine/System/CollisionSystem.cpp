#include "EnginePch.h"
#include "CollisionSystem.h"
#include "GameObject/GameObject.h"
#include "Component/MovementComponent.h"

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
		bool collision = false;

		if (m_boxes.size())
		{
			for (unsigned int i = 0; i < m_boxes.size(); ++i)
			{
				auto box = m_boxes[i];
				box->getOwner().isColliding(false);
				collision = false;

				if(box->getOwner().isMoving() || box->getOwner().isJumping())
				{
					for (unsigned int j = 0; j < m_boxes.size() && !collision ; ++j)
					{
						auto otherBox = m_boxes[j];
						otherBox->getOwner().isColliding(false);

						if (box != otherBox && collide(*box, *otherBox))
						{
							box->getOwner().isColliding(true);
							otherBox->getOwner().isColliding(true);
							collision = true;
						}
					}

					if (!collision)
					{
						for (SphereCollider* sphere : m_spheres)
						{
							if (collide(*box, *sphere))
							{
								box->getOwner().isColliding(true);
								sphere->getOwner().isColliding(true);
								collision = true;
								break;
							}
						}
					}

					if (!collision)
					{
						for (PointCollider* point : m_points)
						{
							if (collide(*box, *point))
							{
								box->getOwner().isColliding(true);
								point->getOwner().isColliding(true);
								collision = true;
								break;
							}
						}
					}
				}
			}
		}
		else if (m_spheres.size())
		{
			for (unsigned int i = 0; i < m_spheres.size(); ++i)
			{
				auto sphere = m_spheres[i];
				if (sphere->getOwner().isMoving() || sphere->getOwner().isJumping())
				{
					for (unsigned int j = i + 1; j < m_spheres.size(); ++j)
					{
						auto otherSphere = m_spheres[j];

						if (collide(*sphere, *otherSphere))
						{
							sphere->getOwner().isColliding(true);
							otherSphere->getOwner().isColliding(true);
						}
					}

					for (PointCollider* point : m_points)
					{
						if (collide(*sphere, *point))
						{
							sphere->getOwner().isColliding(true);
							point->getOwner().isColliding(true);
						}
					}
				}
			}
		}
		else if (m_points.size())
		{
			for (unsigned int i = 0; i < m_points.size(); ++i)
			{
				auto point = m_points[i];
				if (point->getOwner().isMoving() || point->getOwner().isJumping())
				{
					for (unsigned int j = i + 1; j < m_points.size(); ++j)
					{
						auto otherPoint = m_points[j];

						if (collide(*point, *otherPoint))
						{
							point->getOwner().isColliding(true);
							otherPoint->getOwner().isColliding(true);
						}
					}
				}
			}
		}
	}

	bool CollisionSystem::collide(
		const BoxCollider& b1,
		const BoxCollider& b2
	)
	{
		return (b1.getMin().x < b2.getMax().x && b1.getMax().x > b2.getMin().x) &&
			   (b1.getMin().y < b2.getMax().y && b1.getMax().y > b2.getMin().y) &&
			   (b1.getMin().z < b2.getMax().z && b1.getMax().z > b2.getMin().z);
	}

	bool CollisionSystem::collide(
		const SphereCollider& s1,
		const SphereCollider& s2
	)
	{
		float distance = glm::distance(s1.getCenter(), s2.getCenter());
		return distance <= (s1.getRadius() + s2.getRadius());
	}

	bool CollisionSystem::collide(
		const PointCollider& p1,
		const PointCollider& p2
	)
	{
		return p1.getCenter() == p2.getCenter();
	}

	bool CollisionSystem::collide(
		const BoxCollider& b,
		const SphereCollider& s
	)
	{
		float x = std::max(b.getMin().x, std::min(s.getCenter().x, b.getMax().x));
		float y = std::max(b.getMin().y, std::min(s.getCenter().y, b.getMax().y));
		float z = std::max(b.getMin().z, std::min(s.getCenter().z, b.getMax().z));

		float distance = glm::distance(Vec3(x, y, z), s.getCenter());

		return distance <= s.getRadius();
	}

	bool CollisionSystem::collide(
		const SphereCollider& s,
		const BoxCollider& b
	)
	{
		return collide(b, s);
	}

	bool CollisionSystem::collide(
		const BoxCollider& b,
		const PointCollider& p
	)
	{
		return (p.getCenter().x >= b.getMin().x && p.getCenter().x <= b.getMax().x) &&
			   (p.getCenter().y >= b.getMin().y && p.getCenter().y <= b.getMax().y) &&
			   (p.getCenter().z >= b.getMin().z && p.getCenter().z <= b.getMax().z);
	}

	bool CollisionSystem::collide(
		const PointCollider& p,
		const BoxCollider& b
	)
	{
		return collide(b, p);
	}

	bool CollisionSystem::collide(
		const SphereCollider& s,
		const PointCollider& p
	)
	{
		float distance = glm::distance(s.getCenter(), p.getCenter());
		return distance <= s.getRadius();
	}

	bool CollisionSystem::collide(
		const PointCollider& p,
		const SphereCollider& s
	)
	{
		return collide(s, p);
	}
};