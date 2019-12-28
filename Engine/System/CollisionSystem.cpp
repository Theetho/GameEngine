#include "EnginePch.h"
#include "CollisionSystem.h"
#include "GameObject/GameObject.h"
#include "Component/PhysicsComponent.h"

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
				return Collide((SphereCollider*)first.first, (BoxCollider*)second.first);
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

	Collision CollisionSystem::Collide(
		const BoxCollider* first,
		const BoxCollider* second
	)
	{
		return Collision(
			   (first->GetMin().x <= second->GetMax().x && first->GetMax().x >= second->GetMin().x)
			&& (first->GetMin().y <= second->GetMax().y && first->GetMax().y >= second->GetMin().y)
			&& (first->GetMin().z <= second->GetMax().z && first->GetMax().z >= second->GetMin().z)
			, std::min(std::abs(first->GetMin().y - second->GetMax().y), std::abs(first->GetMax().y - second->GetMin().y))
			, first , second
		);
	}

	Collision CollisionSystem::Collide(
		const SphereCollider* first,
		const SphereCollider* second
	)
	{
		float distance = glm::distance(first->GetCenter(), second->GetCenter());
		return Collision(
				distance <= (first->GetRadius() + second->GetRadius())
			  , distance
			  , first, second
		);
	}

	Collision CollisionSystem::Collide(
		const BoxCollider* box_collider,
		const SphereCollider* sphere_collider
	)
	{
			float x = std::max(box_collider->GetMin().x, std::min(sphere_collider->GetCenter().x, box_collider->GetMax().x));
			float y = std::max(box_collider->GetMin().y, std::min(sphere_collider->GetCenter().y, box_collider->GetMax().y));
			float z = std::max(box_collider->GetMin().z, std::min(sphere_collider->GetCenter().z, box_collider->GetMax().z));

			float distance = glm::distance(Vec3(x, y, z), sphere_collider->GetCenter());

			return Collision(
				distance <= sphere_collider->GetRadius()
			  , std::min(std::abs(sphere_collider->GetCenter().y - box_collider->GetMax().y), std::abs(sphere_collider->GetCenter().y - box_collider->GetMin().y))
			  , box_collider, sphere_collider
			);
	}

	Collision CollisionSystem::Collide(
		const SphereCollider* sphere_collider,
		const BoxCollider* box_collider
	)
	{
		return Collide(box_collider, sphere_collider);
	}
};