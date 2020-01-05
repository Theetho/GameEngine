#include "CBoxCollider.h"
#include "CPhysicsEngine.h"

CBoxCollider::CBoxCollider(CGameObject& gameObject, sf::Vector2f center, sf::Vector2f bounds)
	: CCollider(gameObject, center, bounds)
{
	CPhysicsEngine::AddCollider(this);
}

CBoxCollider::~CBoxCollider()
{
	CPhysicsEngine::RemoveCollider(this);
}

sf::Vector2f CBoxCollider::GetPointOnBounds(const SRay& velocity)
{
	//float ratio = std::min(mBounds.x / std::abs(velocity.direction.x), mBounds.y / std::abs(velocity.direction.y));

	return mCenter;// +(velocity.direction * ratio);
}

sf::Vector2f CBoxCollider::GetNormalAtPoint(const sf::Vector2f& point)
{
	auto newPoint = mCenter - point;

	return sf::Vector2f(
	//	std::abs(newPoint.x) == mBounds.x ? (newPoint.x / std::abs(newPoint.x)) : 0.0f,
	//	std::abs(newPoint.y) == mBounds.y ? (newPoint.y / std::abs(newPoint.y)) : 0.0f
	);
}
