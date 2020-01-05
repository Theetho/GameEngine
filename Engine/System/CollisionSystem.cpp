#include "EnginePch.h"
#include "CollisionSystem.h"
#include "GameObject/GameObject.h"
#include "Component/PhysicsComponent.h"
#include "Util/Benchmark.h"

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
		CheckForMovingObjectsCollisions();
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
		return std::make_shared<CollisionSystem>();
	}

	Ref<CollisionSystem> CollisionSystem::Get()
	{
		return sInstance;
	}
		
	void CollisionSystem::CheckForMovingObjectsCollisions()
	{
		// Only Check the collisions for moveable objects
		for (auto iterator : mMoveableColliders)
		{
			Collider* collider = iterator.first;

			if (collider->GetRigidBody()->IsUsingGravity())
				collider->GetRigidBody()->GetVelocity().y -= 9.81f;

			collider->GetGameObject().SetIsColliding(false);
			// Check for collisions with the other moveable colliders
			auto moveable_iterator = mMoveableColliders.end();
			while ((--moveable_iterator)->first != collider)
			{
				Collider* moveable_collider = moveable_iterator->first;

				Collision collision = Collide(iterator, *moveable_iterator);
				if (collision.IsColliding())
				{
					collider->GetGameObject().OnCollision(collision);
				}
			}
			// Same with static colliders
			for (auto static_iterator : mStaticColliders)
			{
				Collider* staticCollider = static_iterator.first;
				
				Collision collision = Collide(iterator, static_iterator);
				if (collision.IsColliding())
				{
					collider->GetGameObject().OnCollision(collision);
				}
			}
			// Then we check if the game object is not below the terrain
			for (auto terrain : mTerrains)
			{
				auto height = terrain->GetGroundLevel(collider->GetGameObject());
				
				/*auto physics = collider->GetGameObject().GetComponent<PhysicsComponent>();
				if (physics)
					physics->SetGroundLevel(height);*/

				//if (collider->GetGameObject().GetTransform().GetPosition().y < height)
				auto rigid_body = collider->GetRigidBody();
				rigid_body->SetGroundLevel(terrain->GetGroundLevel(collider->GetGameObject()));
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
			return Collision(false, 0.0f, first.first, second.first);
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
		float distance_up_axis = std::min(std::abs(first->GetMin().y - second->GetMax().y), std::abs(first->GetMax().y - second->GetMin().y));
		
		return Collision(collide, distance_up_axis, first, second);
	}

	Collision CollisionSystem::Collide(const SphereCollider* first, const SphereCollider* second)
	{
		float distance = glm::distance(first->GetCenter(), second->GetCenter());
		bool collide   = distance <= (first->GetRadius() + second->GetRadius());
		
		return Collision(collide, distance, first, second);
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
		float distance_up_axis = y - sphere_collider->GetCenter().y + sphere_collider->GetRadius();

		return Collision(collide, distance_up_axis, box_collider, sphere_collider);
	}
};