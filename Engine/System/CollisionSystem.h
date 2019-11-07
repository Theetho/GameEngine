#pragma once
#include "Component/Collider.h"

namespace Engine
{
	class CollisionSystem
	{
	public:
		CollisionSystem();

		~CollisionSystem();

		void onUpdate(
			const double& delta
		);

		inline static Ref<CollisionSystem> Create()
		{
			return std::make_shared<CollisionSystem>();
		}

		inline static Ref<CollisionSystem> Get()
		{
			return s_instance;
		}

		static void AddCollider(
			BoxCollider* collider
		)
		{
			if (s_instance)
				s_instance->m_boxes.push_back(collider);
		}
		
		static void AddCollider(
			SphereCollider* collider
		)
		{
			if (s_instance)
				s_instance->m_spheres.push_back(collider);
		}

		static void AddCollider(
			PointCollider* collider
		)
		{
			if (s_instance)
				s_instance->m_points.push_back(collider);
		}

		static void RemoveCollider(
			BoxCollider* collider
		)
		{
			if (s_instance)
			{
				auto& boxes = s_instance->m_boxes;
				for (unsigned int i = 0; i < boxes.size(); ++i)
				{
					if (boxes[i] == collider)
					{
						boxes.erase(boxes.begin() + i, boxes.begin() + i + 1);
					}
				}
			}
		}

		static void RemoveCollider(
			SphereCollider* collider
		)
		{
			if (s_instance)
			{
				auto& spheres = s_instance->m_spheres;
				for (unsigned int i = 0; i < spheres.size(); ++i)
				{
					if (spheres[i] == collider)
					{
						spheres.erase(spheres.begin() + i, spheres.begin() + i + 1);
					}
				}
			}
		}

		static void RemoveCollider(
			PointCollider* collider
		)
		{
			if (s_instance)
			{
				auto& points = s_instance->m_points;
				for (unsigned int i = 0; i < points.size(); ++i)
				{
					if (points[i] == collider)
					{
						points.erase(points.begin() + i, points.begin() + i + 1);
					}
				}
			}
		}
	private:
		static Ref<CollisionSystem> s_instance;

		std::vector<BoxCollider*>    m_boxes;
		std::vector<SphereCollider*> m_spheres;
		std::vector<PointCollider*>  m_points;

		// Check only if moving objects collide with at least one other object
		// (stop when the first collision is found for each moving object) 
		void checkForOneCollision();

		// Check for collision between every object (even the static ones)
		void checkForAllCollision();

		bool collide(
			const BoxCollider* b1,
			const BoxCollider* b2
		);

		bool collide(
			const SphereCollider* s1,
			const SphereCollider* s2
		);

		bool collide(
			const PointCollider* p1,
			const PointCollider* p2
		);

		bool collide(
			const BoxCollider* b,
			const SphereCollider* s
		);

		bool collide(
			const SphereCollider* s,
			const BoxCollider* b
		);

		bool collide(
			const BoxCollider* b,
			const PointCollider* p
		);

		bool collide(
			const PointCollider* p,
			const BoxCollider* b
		);

		bool collide(
			const SphereCollider* s,
			const PointCollider* p
		);

		bool collide(
			const PointCollider* p,
			const SphereCollider* s
		);
	};
}
