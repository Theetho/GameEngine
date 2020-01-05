#include "CSphereCollider.h"
#include "CPhysicsEngine.h"
#include "CMaths.h"

CSphereCollider::CSphereCollider(CGameObject& gameObject, sf::Vector2f center, sf::Vector2f bounds)
	: CCollider(gameObject, center, bounds)
{
	CPhysicsEngine::AddCollider(this);
}

CSphereCollider::~CSphereCollider()
{
	CPhysicsEngine::RemoveCollider(this);
}

sf::Vector2f CSphereCollider::GetPointOnBounds(const SRay& velocity)
{
	return mCenter;// + (velocity.direction * mBounds.y);
}

sf::Vector2f CSphereCollider::GetNormalAtPoint(const sf::Vector2f& point)
{
	return - Normalize(point - mCenter);
}
