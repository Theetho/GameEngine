#include "BoxCollider.h"

BoxCollider::BoxCollider(GameObject& gameObject, sf::Vector2f center, sf::Vector2f bounds)
	: Collider(gameObject, center, bounds)
{
}

BoxCollider::~BoxCollider()
{
}

sf::Vector2f BoxCollider::GetPointOnBounds(const sf::Vector2f& direction)
{
	float ratio = std::min(mBounds.x / std::abs(direction.x), mBounds.y / std::abs(direction.y));

	return direction * ratio;
}
