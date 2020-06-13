#include "EnginePch.h"
#include "CollisionSystem.h"
#include "GameObject/GameObject.h"
#include "Include/Component.h"

namespace Engine
{
	Ref<CollisionSystem> CollisionSystem::sInstance = CollisionSystem::Create();

	CollisionSystem::CollisionSystem()
	{
		ENGINE_ASSERT(!sInstance, "A collision system instance already exists");
	}

	CollisionSystem::~CollisionSystem()
	{}

	void CollisionSystem::OnUpdate(const double& delta)
	{
		CheckForMovingObjectsCollisions(delta);
	}

	void CollisionSystem::AddTerrain(TerrainCollider* collider)
	{
		sInstance->mTerrains.push_back(collider);
	}

	void CollisionSystem::RemoveCollider(Collider* collider)
	{
		if (sInstance)
		{
			if (sInstance->mMoveableColliders.count(collider))
			{
				sInstance->mMoveableColliders.erase(collider);
			}
			else if (sInstance->mStaticColliders.count(collider))
			{
				sInstance->mStaticColliders.erase(collider);
			}
			else
			{
				sInstance->mTerrains.erase(
					std::remove_if(
						sInstance->mTerrains.begin(),
						sInstance->mTerrains.end(),
						[collider](const TerrainCollider* terrain)
						{
							return terrain == collider;
						}
					),
					sInstance->mTerrains.end()
				);
			}
		}
	}

	Ref<CollisionSystem> CollisionSystem::Create()
	{
		return CreateRef<CollisionSystem>();
	}

	Ref<CollisionSystem> CollisionSystem::Get()
	{
		return sInstance;
	}
		
	void CollisionSystem::CheckForMovingObjectsCollisions(const double& delta)
	{
		// Only Check the collisions for moveable objects
		for (auto iterator : mMoveableColliders)
		{
			Collider* collider = iterator.first;

			// Apply gravity
			if (collider->GetRigidBody()->IsUsingGravity())
			{
				float gravity = GRAVITY_ACCELERATION * delta;
				collider->GetRigidBody()->mVelocity.regular.y += gravity;
			}

			collider->GetGameObject().SetIsColliding(false);
			// Check for collisions with the other moveable colliders
			auto moveable_iterator = mMoveableColliders.end();
			while ((--moveable_iterator)->first != collider)
			{
				Collider* moveable_collider = moveable_iterator->first;

				Collision collision = Collide(iterator, *moveable_iterator);
				if (collision.IsColliding)
				{
					collider->GetGameObject().OnCollision(collision);
				}
			}
			// Same with static colliders
			for (auto static_iterator : mStaticColliders)
			{
				Collider* staticCollider = static_iterator.first;
				
				Collision collision = Collide(iterator, static_iterator);
				if (collision.IsColliding)
				{
					collider->GetGameObject().OnCollision(collision);
				}
			}
			// Then we check if the game object is not below the terrain
			auto terrain = mTerrains.begin();
			// Find the terrain on which it moves
			while (terrain != mTerrains.end() && !(*terrain)->Contains(collider->GetCenter()))
			{
				++terrain;
			}
			if (terrain != mTerrains.end())
			{
				// Then we get the height at the object's position
				float height = (*terrain)->GetGroundLevel(collider->GetCenter());

				float size_y = collider->GetCenter().y - collider->GetMin().y;
				collider->GetRigidBody()->SetGroundLevel(height + size_y);
			}
		}
	}

	Collision CollisionSystem::Collide(
		const std::pair<Collider*, std::type_index>& first,
		const std::pair<Collider*, std::type_index>& second
	)
	{
		if (first.second == typeid(BoxCollider))
		{
			if (second.second == typeid(BoxCollider))
			{
				return Collide((BoxCollider*)first.first, (BoxCollider*)second.first);
			}
			else if (second.second == typeid(SphereCollider))
			{
				return Collide((BoxCollider*)first.first, (SphereCollider*)second.first);
			}
		}
		else if (first.second == typeid(SphereCollider))
		{
			if (second.second == typeid(BoxCollider))
			{
				return Collide((BoxCollider*)second.first, (SphereCollider*)first.first);
			}
			else if (second.second == typeid(SphereCollider))
			{
				return Collide((SphereCollider*)first.first, (SphereCollider*)second.first);
			}
		}
		else
		{
			std::cout << "This collider is not handled by the system" << std::endl;
			return Collision(false, 0.0f, 0.0f, 0.0f);
		}
	}

	Collision CollisionSystem::Collide(const BoxCollider* first, const BoxCollider* second)
	{
		bool collide = first->GetMin().x <= second->GetMax().x 
					&& first->GetMax().x >= second->GetMin().x
					&& first->GetMin().y <= second->GetMax().y 
					&& first->GetMax().y >= second->GetMin().y
					&& first->GetMin().z <= second->GetMax().z 
					&& first->GetMax().z >= second->GetMin().z;
		float x = std::min(std::abs(first->GetMin().x - second->GetMax().x), std::abs(first->GetMax().x - second->GetMin().x));
		float y = std::min(std::abs(first->GetMin().y - second->GetMax().y), std::abs(first->GetMax().y - second->GetMin().y));
		float z = std::min(std::abs(first->GetMin().z - second->GetMax().z), std::abs(first->GetMax().z - second->GetMin().z));
		
		return Collision(collide, x, y, z);
	}

	Collision CollisionSystem::Collide(const SphereCollider* first, const SphereCollider* second)
	{
		float distance = glm::distance(first->GetCenter(), second->GetCenter());
		bool collide   = distance <= (first->GetRadius() + second->GetRadius());
		float x = std::abs(first->GetCenter().x - second->GetCenter().x);
		float y = std::abs(first->GetCenter().y - second->GetCenter().y);
		float z = std::abs(first->GetCenter().z - second->GetCenter().z);
		
		return Collision(collide, x, y, z);
	}

	Collision CollisionSystem::Collide(const BoxCollider* box_collider, const SphereCollider* sphere_collider)
	{
		// Get box closest point to sphere center by clamping
		float x = std::max(box_collider->GetMin().x, std::min(sphere_collider->GetCenter().x, box_collider->GetMax().x));
		float y = std::max(box_collider->GetMin().y, std::min(sphere_collider->GetCenter().y, box_collider->GetMax().y));
		float z = std::max(box_collider->GetMin().z, std::min(sphere_collider->GetCenter().z, box_collider->GetMax().z));

		float distance = (x - sphere_collider->GetCenter().x) * (x - sphere_collider->GetCenter().x) +
						 (y - sphere_collider->GetCenter().y) * (y - sphere_collider->GetCenter().y) +
						 (z - sphere_collider->GetCenter().z) * (z - sphere_collider->GetCenter().z);

		bool collide = distance < (sphere_collider->GetRadius() * sphere_collider->GetRadius());
		x -= sphere_collider->GetCenter().x + sphere_collider->GetRadius();
		y -= sphere_collider->GetCenter().y + sphere_collider->GetRadius();
		z -= sphere_collider->GetCenter().z + sphere_collider->GetRadius();

		return Collision(collide, x, y, z);
	}
};