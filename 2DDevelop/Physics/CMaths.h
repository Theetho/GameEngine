#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>

template <class T>
std::ostream& operator<<(std::ostream& stream, const sf::Vector2<T>& vector)
{
	stream << vector.x << " " << vector.y;
	return stream;
}

template <class T>
float Length(const sf::Vector2<T>& vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

template <class T>
float Dot(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

template <class T>
sf::Vector2<T> operator*(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2)
{
	return sf::Vector2<T>(v1.x * v2.x, v1.y * v2.y);
}

template <class T>
sf::Vector2<T> Normalize(const sf::Vector2<T>& V)
{
	return V / Length(V);
}

template <class T>
sf::Vector2<T> Reflect(const sf::Vector2<T>& V, const sf::Vector2<T>& N)
{
	auto NN = Normalize(N);
	return NN * (2.0f * Dot(V, NN)) - V;
}

struct SRay
{
	sf::Vector2f position;
	sf::Vector2f direction;
	SRay(const sf::Vector2f& position, const sf::Vector2f& direction)
		: position(position)
		, direction(direction)
	{
	}
};