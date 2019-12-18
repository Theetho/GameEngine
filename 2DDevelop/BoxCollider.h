#pragma once
#include "Collider.h"
class BoxCollider : public Collider
{
public:
	BoxCollider(GameObject& gameObject, sf::Vector2f center, sf::Vector2f bounds);
	~BoxCollider();

	virtual sf::Vector2f GetPointOnBounds(const sf::Vector2f& direction) override;
};

