#pragma once

#include "Component/Collider.h"
#include "GameObject/GameObject.h"

namespace Engine
{
	class CollisionSystem
	{
	public:
		CollisionSystem();
		~CollisionSystem();

		void OnUpdate(const double& delta);

		static Ref<CollisionSystem> Get();
		template<typename T>
		static void AddCollider(Collider* collider)
		{
			static_assert(std::is_base_of<Collider, T>::value, "T is not a collider");
			
			if (sInstance)
			{
				auto rigid_body = collider->GetGameObject().GetComponent<RigidBody>();
				if (rigid_body && !sInstance->mMoveableColliders.count(collider))
				{
					sInstance->mMoveableColliders.insert(std::pair<Collider*, std::type_index>(collider,typeid(T)));
				}
				else if (!sInstance->mStaticColliders.count(collider))
				{
					sInstance->mStaticColliders.insert(std::pair<Collider*, std::type_index>(collider, typeid(T)));
				}
			}
		}
		static void AddTerrain(TerrainCollider* collider);
		static void RemoveCollider(Collider* collider);
	private:
		static Ref<CollisionSystem> Create();
		static Ref<CollisionSystem> sInstance;

		std::unordered_map<Collider*, std::type_index> mMoveableColliders;
		std::unordered_map<Collider*, std::type_index> mStaticColliders;
		std::vector<TerrainCollider*>				   mTerrains;

		void CheckForMovingObjectsCollisions();

		Collision Collide(const std::pair<Collider*, std::type_index>& first, const std::pair<Collider*, std::type_index>& second);
		Collision Collide(const BoxCollider* first, const BoxCollider* second);
		Collision Collide(const SphereCollider* first, const SphereCollider* second);
		Collision Collide(const BoxCollider* box_collider, const SphereCollider* sphere_collider);
	};
}
