#pragma once

#include "SFML/Graphics.hpp"

template <class T>
float length(const sf::Vector2<T>& vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}