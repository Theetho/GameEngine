#pragma once

namespace Engine
{
	class Collider;
	class TerrainCollider;
	class BoxCollider;
	class SphereCollider;
	
	// Struct that stores data of a collision
	struct Collision
	{
		Collision(bool collide, float distance_x, float distance_y, float distance_z)
			: IsColliding(collide), PenetrationDistance(distance_x, distance_y, distance_z)
		{}
		// Boolean to tell whether their is collision
		const bool IsColliding;
		// The distance beetween the two colliders on each axis
		const Vec3 PenetrationDistance;
	};

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

		const float GRAVITY_ACCELERATION = -9.81f;

		std::unordered_map<Collider*, std::type_index> mMoveableColliders;
		std::unordered_map<Collider*, std::type_index> mStaticColliders;
		std::vector<TerrainCollider*>				   mTerrains;

		void CheckForMovingObjectsCollisions(const double& delta);

		Collision Collide(const std::pair<Collider*, std::type_index>& first, const std::pair<Collider*, std::type_index>& second);
		Collision Collide(const BoxCollider* first, const BoxCollider* second);
		Collision Collide(const SphereCollider* first, const SphereCollider* second);
		Collision Collide(const BoxCollider* box_collider, const SphereCollider* sphere_collider);
	};
}
