#pragma once

namespace Engine
{
	class BoxCollider;
	class SphereCollider;
	class PointCollider;

	class CollisionSystem
	{
	public:
		void onUpdate(
			const double& delta
		);

		static CollisionSystem* Get()
		{
			if (!s_instance)
				s_instance = new CollisionSystem;
			return s_instance;
		}

		static void addCollider(
			BoxCollider* collider
		)
		{
			s_instance->m_boxes.insert(collider);
		}
		
		static void addCollider(
			SphereCollider* collider
		)
		{
			s_instance->m_spheres.insert(collider);
		}
		
		static void addCollider(
			PointCollider* collider
		)
		{
			s_instance->m_points.insert(collider);
		}
	private:
		CollisionSystem() {}

		~CollisionSystem() {}

		static CollisionSystem* s_instance;

		std::set<BoxCollider*>    m_boxes;
		std::set<SphereCollider*> m_spheres;
		std::set<PointCollider*>  m_points;

		bool collide(
			const BoxCollider& b1,
			const BoxCollider& b2
		);

		bool collide(
			const SphereCollider& s1,
			const SphereCollider& s2
		);

		bool collide(
			const PointCollider& p1,
			const PointCollider& p2
		);

		bool collide(
			const BoxCollider& b,
			const SphereCollider& s
		);

		bool collide(
			const SphereCollider& s,
			const BoxCollider& b
		);

		bool collide(
			const BoxCollider& b,
			const PointCollider& p
		);

		bool collide(
			const PointCollider& p,
			const BoxCollider& b
		);

		bool collide(
			const SphereCollider& s,
			const PointCollider& p
		);

		bool collide(
			const PointCollider& p,
			const SphereCollider& s
		);
	};
}
