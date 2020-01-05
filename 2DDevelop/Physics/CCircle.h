#pragma once

#include "CGameObject.h"

class CCircle : public CGameObject, public sf::CircleShape
{
public:
	CCircle(
		float radius,
		const sf::Vector2f& position,
		const sf::Vector2f& rotation = sf::Vector2f(0.0f, 0.0f)
	);
	~CCircle();

	void OnUpdate(const double& delta) override;
};

