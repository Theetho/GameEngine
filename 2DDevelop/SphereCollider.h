#pragma once

#include "Collider.h"

class SphereCollider : public Collider
{
public:
	SphereCollider(GameObject& gameObject, sf::Vector2f center, sf::Vector2f bounds);
	~SphereCollider();

	virtual sf::Vector2f GetPointOnBounds(const sf::Vector2f& direction) override;
};

