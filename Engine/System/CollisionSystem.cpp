#include "EnginePch.h"
#include "CollisionSystem.h"
#include "GameObject/GameObject.h"
#include "Component/MovementComponent.h"
#include "Component/ColliderComponent.h"

namespace Engine
{
	CollisionSystem* CollisionSystem::s_instance = nullptr;

	void CollisionSystem::onUpdate(const double& delta)
	{
		bool colision;

		std::set<BoxCollider*>    boxes;
		std::set<SphereCollider*> spheres;
		std::set<PointCollider*>  points;

		if (m_boxes.size())
		{
			for (BoxCollider* box : m_boxes)
			{

				if (box->m_owner->isMoving() || box->m_owner->isJumping())
				{
					for (BoxCollider* otherBox : m_boxes)
					{
						if (box != otherBox && !boxes.count(otherBox))
						{
							colision = collide(*box, *otherBox);

							box->m_owner->isColliding(colision);
							otherBox->m_owner->isColliding(colision);
						}
					}

					boxes.insert(box);

					for (SphereCollider* sphere : m_spheres)
					{
						colision = collide(*box, *sphere);

						box->m_owner->isColliding(colision);
						sphere->m_owner->isColliding(colision);

					}
					for (PointCollider* point : m_points)
					{
						colision = collide(*box, *point);

						box->m_owner->isColliding(colision);
						point->m_owner->isColliding(colision);
					}
				}
			}
		}
		else if (m_spheres.size())
		{
			for (SphereCollider* sphere : m_spheres)
			{
				if (sphere->m_owner->isMoving() || sphere->m_owner->isJumping())
				{
					for (SphereCollider* otherSphere : m_spheres)
					{
						if (sphere != otherSphere && !spheres.count(otherSphere))
						{
							colision = collide(*sphere, *otherSphere);

							sphere->m_owner->isColliding(colision);
							otherSphere->m_owner->isColliding(colision);
						}
					}

					spheres.insert(sphere);

					for (PointCollider* point : m_points)
					{
						colision = collide(*sphere, *point);

						sphere->m_owner->isColliding(colision);
						point->m_owner->isColliding(colision);
					}
				}
			}
		}
		else if (m_points.size())
		{
			for (PointCollider* point : m_points)
			{
				if (point->m_owner->isMoving() || point->m_owner->isJumping())
				{
					for (PointCollider* otherPoint : m_points)
					{
						if (point != otherPoint && !points.count(otherPoint))
						{
							colision = collide(*point, *otherPoint);

							point->m_owner->isColliding(colision);
							otherPoint->m_owner->isColliding(colision);
						}
					}

					points.insert(point);
				}
			}
		}
	}

	bool CollisionSystem::collide(
		const BoxCollider& b1,
		const BoxCollider& b2
	)
	{
		return (b1.m_min.x < b2.m_max.x && b1.m_max.x > b2.m_min.x) &&
			   (b1.m_min.y < b2.m_max.y && b1.m_max.y > b2.m_min.y) &&
			   (b1.m_min.z < b2.m_max.z && b1.m_max.z > b2.m_min.z);
	}

	bool CollisionSystem::collide(
		const SphereCollider& s1,
		const SphereCollider& s2
	)
	{
		float distance = glm::distance(s1.m_center, s2.m_center);
		return distance < (s1.m_radius + s2.m_radius);
	}

	bool CollisionSystem::collide(
		const PointCollider& p1,
		const PointCollider& p2
	)
	{
		return p1.m_center == p2.m_center;
	}

	bool CollisionSystem::collide(
		const BoxCollider& b,
		const SphereCollider& s
	)
	{
		float x = std::max(b.m_min.x, std::min(s.m_center.x, b.m_max.x));
		float y = std::max(b.m_min.y, std::min(s.m_center.y, b.m_max.y));
		float z = std::max(b.m_min.z, std::min(s.m_center.z, b.m_max.z));

		float distance = glm::distance(Vec3(x, y, z), s.m_center);

		return distance < s.m_radius;
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
		return (p.m_center.x > b.m_min.x && p.m_center.x < b.m_max.x) &&
			   (p.m_center.y > b.m_min.y && p.m_center.y < b.m_max.y) &&
			   (p.m_center.z > b.m_min.z && p.m_center.z < b.m_max.z);
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
		float distance = glm::distance(s.m_center, p.m_center);
		return distance < s.m_radius;
	}

	bool CollisionSystem::collide(
		const PointCollider& p,
		const SphereCollider& s
	)
	{
		return collide(s, p);
	}
};