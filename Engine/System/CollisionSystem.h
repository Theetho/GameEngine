#pragma once
#include "Component/Collider.h"

namespace Engine
{
	class CollisionSystem
	{
	public:
		CollisionSystem();
		~CollisionSystem();

		void OnUpdate(const double& delta);

		static Ref<CollisionSystem> Create();
		static Ref<CollisionSystem> Get();

		template<typename T>
		static void AddCollider(Collider* collider)
		{
			static_assert(std::is_base_of<Collider, T>::value, "T is not a collider");
			
			if (sInstance)
			{
				if (collider->GetGameObject().IsMoveable() && !sInstance->mMoveableColliders.count(collider))
				{
					sInstance->mMoveableColliders.insert(std::pair<Collider*, std::type_index>(collider,typeid(T)));
				}
				else if (!sInstance->mStaticColliders.count(collider))
				{
					sInstance->mStaticColliders.insert(std::pair<Collider*, std::type_index>(collider, typeid(T)));
				}
			}
		}

		static void RemoveCollider(
			Collider* collider
		)
		{
			if (sInstance)
			{
				if (sInstance->mMoveableColliders.count(collider))
				{
					sInstance->mMoveableColliders.erase(collider);
				}
				else
				{
					sInstance->mStaticColliders.erase(collider);
				}
			}
		}

	private:
		static Ref<CollisionSystem> sInstance;

		std::unordered_map<Collider*, std::type_index> mMoveableColliders;
		std::unordered_map<Collider*, std::type_index> mStaticColliders;

		void CheckForMovingObjectsCollisions();

		Collision Collide(
			const std::pair<Collider*, std::type_index>& first,
			const std::pair<Collider*, std::type_index>& second
		);

		Collision Collide(
			const BoxCollider* first,
			const BoxCollider* second
		);

		Collision Collide(
			const SphereCollider* first,
			const SphereCollider* second

		);

		Collision Collide(
			const BoxCollider* box_collider,
			const SphereCollider* sphere_collider
		);

		Collision Collide(
			const SphereCollider* sphere_collider,
			const BoxCollider* box_collider
		);
	};
}
