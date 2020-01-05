#include "CCircle.h"
#include "CSphereCollider.h"

CCircle::CCircle(
	float radius,
	const sf::Vector2f& position,
	const sf::Vector2f& rotation
)
	: CGameObject(position, rotation)
	, CircleShape(radius)
{
	setPosition(position - sf::Vector2f(radius, radius));
	mCollider = new CSphereCollider(*this, position, sf::Vector2f(radius, radius));
}

CCircle::~CCircle()
{
}

void CCircle::OnUpdate(const double& delta)
{
	mCollider->OnUdpate(delta);
}
