#include "SphereCollider.h"

SphereCollider::SphereCollider(GameObject& gameObject, sf::Vector2f center, sf::Vector2f bounds)
	: Collider(gameObject, center, bounds)
{}

SphereCollider::~SphereCollider()
{}

sf::Vector2f SphereCollider::GetPointOnBounds(const sf::Vector2f& direction)
{
	return direction * mBounds.y;
}