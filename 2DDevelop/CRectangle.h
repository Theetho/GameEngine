#pragma once

#include "CGameObject.h"
#include "SFML/Graphics/RectangleShape.hpp"

class CRectangle : public CGameObject, public sf::RectangleShape
{
public:
	CRectangle(
		const sf::Vector2f& dimension,
		const sf::Vector2f& position,
		const sf::Vector2f& rotation = sf::Vector2f(0.0f, 0.0f)
	);
	~CRectangle();

	void OnUpdate(const double& delta) override;
};

