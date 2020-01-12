#include "CPhysicsEngine.h"
#include <algorithm>
#include "CMaths.h"
//#include "CWindow.h"

CPhysicsEngine* CPhysicsEngine::sInstance = new CPhysicsEngine();

CPhysicsEngine* CPhysicsEngine::GetInstance()
{
	return sInstance;
}

void CPhysicsEngine::AddCollider(CCollider* collider)
{
	sInstance->mColliders.push_back(collider);
}

void CPhysicsEngine::RemoveCollider(CCollider* collider)
{
	std::remove_if(sInstance->mColliders.begin(), sInstance->mColliders.end(),
		[collider](CCollider* mCollider)
		{
			return mCollider == collider;
		}
	);
}

void CPhysicsEngine::OnUpdate(const double& delta)
{
	std::sort(mColliders.begin(), mColliders.end(),
		[](CCollider* first, CCollider* second)
		{
			return first->mRigidBody;
		}
	);

	this->ApplyForces(mColliders, delta);
	this->ResolveCollision(mColliders, delta);
}

void CPhysicsEngine::ApplyForces(std::vector<CCollider*>& colliders, const double& delta)
{
	size_t i = 0;
	while (colliders[i]->mRigidBody)
	{
		// Gravity 
		colliders[i]->mRigidBody->mVelocity.y += GRAVITATIONAL_ACCELERATION * delta;
		// Friction x
		if (colliders[i]->mRigidBody->mVelocity.x < 0)
		{
			colliders[i]->mRigidBody->mVelocity.x += FRICTION * delta;
			colliders[i]->mRigidBody->mVelocity.x = std::min(colliders[i]->mRigidBody->mVelocity.x, 0.0f);
		}
		else
		{
			colliders[i]->mRigidBody->mVelocity.x -= FRICTION * delta;
			colliders[i]->mRigidBody->mVelocity.x = std::max(colliders[i]->mRigidBody->mVelocity.x, 0.0f);
		}
		// Friction y
		/*if (colliders[i]->mRigidBody->mVelocity.y < 0)
		{
			colliders[i]->mRigidBody->mVelocity.y += FRICTION * delta;
			colliders[i]->mRigidBody->mVelocity.y = std::min(colliders[i]->mRigidBody->mVelocity.y, 0.0f);
		}
		else
		{
			colliders[i]->mRigidBody->mVelocity.y -= FRICTION * delta;
			colliders[i]->mRigidBody->mVelocity.y = std::max(colliders[i]->mRigidBody->mVelocity.y, 0.0f);
		}*/
		++i;
	}
}

void CPhysicsEngine::ResolveCollision(std::vector<CCollider*>& colliders, const double& delta)
{
	size_t i = 0;
	while (i < colliders.size() && colliders[i]->mRigidBody)
	{
		for (size_t j = i + 1; j < colliders.size(); ++j)
		{
			CCollision collision = DetectCollision(colliders[i], colliders[j]);
			// Collision
			if (collision.mCollide)
			{
				collision.mDistance *= delta;
				CallCollisionHandler(collision, colliders[i]);
			}
			else
			{
				if (colliders[i]->mGameObject.mIsColliding)
				{
					colliders[i]->OnCollisionExit();
					colliders[i]->mGameObject.mIsColliding = false;
				}
			}
		}
		++i;
	}
}

CCollision CPhysicsEngine::DetectCollision(CCollider* first, CCollider* second)
{
	sf::Vector2f vectorBetweenCenters = first->mCenter - second->mCenter;
	float distanceBetweenCenters = Length(vectorBetweenCenters);
	auto normalizedVectorBetweenCenters = Normalize(vectorBetweenCenters);

	//auto pointOnFirst  = first->GetPointOnBounds(SRay(first->mCenter, first->mRigidBody->GetVelocity()));
	auto pointOnFirst  = first->GetPointOnBounds(SRay(first->mCenter, - normalizedVectorBetweenCenters));
	//auto pointOnSecond = second->GetPointOnBounds(SRay(first->mCenter, -first->mRigidBody->GetVelocity()));
	auto pointOnSecond = second->GetPointOnBounds(SRay(first->mCenter, normalizedVectorBetweenCenters));

	auto vectorBetweenClosestEdges = pointOnFirst - pointOnSecond;
	float distanceBetweenClosestEdges = Length(vectorBetweenClosestEdges);

	bool collide = distanceBetweenClosestEdges <= 10.0f;
	auto normal = second->GetNormalAtPoint(pointOnSecond);

	//if (collide)
	//{
	//	sf::VertexArray betweenCenters(sf::PrimitiveType::LineStrip, 2);
	//	betweenCenters[0].position = pointOnFirst;
	//	betweenCenters[1].position = pointOnFirst - vectorBetweenClosestEdges;
	//	std::cout << distanceBetweenClosestEdges << std::endl;
	//	CWindow::mWindow.draw(betweenCenters);
	//}

	return CCollision(collide, distanceBetweenClosestEdges, normal);
}

void CPhysicsEngine::CallCollisionHandler(const CCollision& collision, CCollider* collider)
{
	if (collider->mGameObject.mIsColliding)
	{
		collider->OnCollisionStay(collision);
	}
	else
	{
		collider->OnCollisionEnter(collision);
		collider->mGameObject.mIsColliding = true;
	}
}
