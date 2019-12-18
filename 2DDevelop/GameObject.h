#pragma once

#include "SFML/Graphics.hpp"

class GameObject
{
public:
	GameObject(
		const sf::Vector2f& position,
		const sf::Vector2f& rotation = sf::Vector2f(0.0f, 0.0f)
	);
	~GameObject();

	const sf::Vector2f& GetPosition() const;
	sf::Vector2f& GetPosition();
	const sf::Vector2f& GetRotation() const;
	sf::Vector2f& GetRotation();
private:
	sf::Vector2f mPosition;
	sf::Vector2f mRotation;
};

