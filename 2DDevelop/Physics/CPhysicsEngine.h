#pragma once

#include <vector>
#include "CCollider.h"
#include "CCollision.h"

class CPhysicsEngine
{
public:
	static CPhysicsEngine* GetInstance();
	static void AddCollider(CCollider* collider);
	static void RemoveCollider(CCollider* collider);

	void OnUpdate(const double& delta);
private:
	CPhysicsEngine() = default;
	~CPhysicsEngine() {}

	void ApplyForces(std::vector<CCollider*>& colliders, const double& delta);
	void ResolveCollision(std::vector<CCollider*>& colliders, const double& delta);
	CCollision DetectCollision(CCollider* first, CCollider* second);
	void CallCollisionHandler(const CCollision& collision, CCollider* collider);

	static CPhysicsEngine* sInstance;

	const float GRAVITATIONAL_ACCELERATION = 9.81f;
	const float FRICTION = 10.0f;
	std::vector<CCollider*> mColliders;
};

