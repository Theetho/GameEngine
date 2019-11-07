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
			s_instance = std::make_shared<CollisionSystem>();
			return s_instance;
		}

		inline static Ref<CollisionSystem> Get()
		{
			return s_instance;
		}

		static void AddCollider(
			Ref<BoxCollider> collider
		)
		{
			if (s_instance)
				s_instance->m_boxes.push_back(collider);
		}
		
		static void AddCollider(
			Ref<SphereCollider> collider
		)
		{
			if (s_instance)
				s_instance->m_spheres.push_back(collider);
		}

		static void AddCollider(
			Ref<PointCollider> collider
		)
		{
			if (s_instance)
				s_instance->m_points.push_back(collider);
		}
	private:
		static Ref<CollisionSystem> s_instance;

		std::vector<Ref<BoxCollider>>    m_boxes;
		std::vector<Ref<SphereCollider>> m_spheres;
		std::vector<Ref<PointCollider>>  m_points;

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
