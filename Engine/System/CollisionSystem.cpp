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
		bool colision;

		std::vector<Ref<BoxCollider>>    boxes;
		std::vector<Ref<SphereCollider>> spheres;
		std::vector<Ref<PointCollider>>  points;

		if (m_boxes.size())
		{
			for (unsigned int i = 0; i < m_boxes.size(); ++i)
			{
				auto& box = m_boxes[i];
				if(box->getOwner().isMoving() || box->getOwner().isJumping())
				{
					for (unsigned int j = i + 1; j < m_boxes.size(); ++j)
					{
						auto& otherBox = m_boxes[j];

						colision = collide(*box, *otherBox);

						box->getOwner().isColliding(colision);
						otherBox->getOwner().isColliding(colision);
					}

					for (Ref<SphereCollider> sphere : m_spheres)
					{
						colision = collide(*box, *sphere);

						box->getOwner().isColliding(colision);
						sphere->getOwner().isColliding(colision);

					}

					for (Ref<PointCollider> point : m_points)
					{
						colision = collide(*box, *point);

						box->getOwner().isColliding(colision);
						point->getOwner().isColliding(colision);
					}
				}
			}
		}
		else if (m_spheres.size())
		{
			for (unsigned int i = 0; i < m_spheres.size(); ++i)
			{
				auto& sphere = m_spheres[i];
				if (sphere->getOwner().isMoving() || sphere->getOwner().isJumping())
				{
					for (unsigned int j = i + 1; j < m_spheres.size(); ++j)
					{
						auto& otherSphere = m_spheres[j];

						colision = collide(*sphere, *otherSphere);

						sphere->getOwner().isColliding(colision);
						otherSphere->getOwner().isColliding(colision);
					}

					for (Ref<PointCollider> point : m_points)
					{
						colision = collide(*sphere, *point);

						sphere->getOwner().isColliding(colision);
						point->getOwner().isColliding(colision);
					}
				}
			}
		}
		else if (m_points.size())
		{
			for (unsigned int i = 0; i < m_points.size(); ++i)
			{
				auto& point = m_points[i];
				if (point->getOwner().isMoving() || point->getOwner().isJumping())
				{
					for (unsigned int j = i + 1; j < m_points.size(); ++j)
					{
						auto& otherPoint = m_points[j];

						colision = collide(*point, *otherPoint);

						point->getOwner().isColliding(colision);
						otherPoint->getOwner().isColliding(colision);
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
		return distance < (s1.getRadius() + s2.getRadius());
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

		return distance < s.getRadius();
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
		return (p.getCenter().x > b.getMin().x && p.getCenter().x < b.getMax().x) &&
			   (p.getCenter().y > b.getMin().y && p.getCenter().y < b.getMax().y) &&
			   (p.getCenter().z > b.getMin().z && p.getCenter().z < b.getMax().z);
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
		return distance < s.getRadius();
	}

	bool CollisionSystem::collide(
		const PointCollider& p,
		const SphereCollider& s
	)
	{
		return collide(s, p);
	}
};