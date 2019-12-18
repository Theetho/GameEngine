#include "PhysicsEngine.h"
#include <algorithm>
#include "Maths.h"

PhysicsEngine* PhysicsEngine::sInstance = new PhysicsEngine();

PhysicsEngine* PhysicsEngine::GetInstance()
{
	return sInstance;
}

void PhysicsEngine::AddCollider(Collider* collider)
{
	sInstance->mColliders.push_back(collider);
}

void PhysicsEngine::RemoveCollider(Collider* collider)
{
	std::remove_if(sInstance->mColliders.begin(), sInstance->mColliders.end(),
		[collider](Collider* mCollider)
		{
			return mCollider == collider;
		}
	);
}

void PhysicsEngine::OnUpdate(const double& delta)
{
	std::sort(mColliders.begin(), mColliders.end(),
		[](Collider* first, Collider second)
		{
			return first->mRigidBody;
		}
	);

	this->ApplyGravity(mColliders);
	this->ResolveCollision(mColliders);
}

void PhysicsEngine::ApplyGravity(std::vector<Collider*>& colliders)
{
	size_t i = 0;
	while (colliders[i]->mRigidBody)
	{
		colliders[i]->mRigidBody->mVelocity.y -= GRAVITATIONAL_ACCELERATION;
		++i;
	}
}

void PhysicsEngine::ResolveCollision(std::vector<Collider*>& colliders)
{
	size_t i = 0;
	while (i < colliders.size() && colliders[i]->mRigidBody)
	{
		for (size_t j = i + 1; j < colliders.size(); ++j)
		{
			Collision collision = DetectCollision(colliders[i], colliders[j]);
		}
		++i;
	}
}

PhysicsEngine::Collision PhysicsEngine::DetectCollision(Collider* first, Collider* second)
{
	sf::Vector2f vectorBetweenCenters = first->mCenter - second->mCenter;
	float distanceBetweenCenters = length(vectorBetweenCenters);
	auto normalizedVectorBetweenCenters = vectorBetweenCenters / distanceBetweenCenters;

	auto vectorOnFirst  = first->GetPointOnBounds(- normalizedVectorBetweenCenters);
	auto vectorOnSecond = second->GetPointOnBounds(normalizedVectorBetweenCenters);

	float distanceBetweenClosestEdges = length(vectorOnFirst - vectorOnSecond);

	bool collide = distanceBetweenClosestEdges == 0;
	float distance = length(first->mCenter - vectorOnSecond);
	auto normal = normalizedVectorBetweenCenters;

	return Collision(collide, distance, normal);
}