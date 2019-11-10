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

		template<typename T>
		inline static void AddCollider(
			Collider* collider
		)
		{
			static_assert(std::is_base_of<Collider, T>::value, "T is not a collider");
			
			if (s_instance)
			{
				if (collider->getOwner().isMoveable() && !s_instance->m_moveableColliders.count(collider))
				{
					s_instance->m_moveableColliders.insert(std::pair<Collider*, std::type_index>(collider,typeid(T)));
				}
				else if (!s_instance->m_staticColliders.count(collider))
				{
					s_instance->m_staticColliders.insert(std::pair<Collider*, std::type_index>(collider, typeid(T)));
				}
			}
		}

		static void RemoveCollider(
			Collider* collider
		)
		{
			if (s_instance)
			{
				if (s_instance->m_moveableColliders.count(collider))
				{
					s_instance->m_moveableColliders.erase(collider);
				}
				else
				{
					s_instance->m_staticColliders.erase(collider);
				}
			}
		}

	private:
		static Ref<CollisionSystem> s_instance;

		std::unordered_map<Collider*, std::type_index> m_moveableColliders;
		std::unordered_map<Collider*, std::type_index> m_staticColliders;

		void checkForMovingObjectsCollisions();

		// Return true if c1 is supposed to be on top of c2,
		// false otherwise
		bool isOnTop(
			Collider* c1,
			const Collider* c2
		);

		bool collide(
			const std::pair<Collider*, std::type_index>& kv1,
			const std::pair<Collider*, std::type_index>& kv2
		);

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
