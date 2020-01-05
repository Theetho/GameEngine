#pragma once

#include "SFML/Graphics.hpp"

struct CCollision
{
	bool mCollide = false;
	float mDistance = 0.0f;
	sf::Vector2f mNormal = sf::Vector2f(0.0f, 0.0f);

	CCollision() = default;
	CCollision(bool collide, float distance, sf::Vector2f normal)
		: mCollide(collide)
		, mDistance(distance)
		, mNormal(normal)
	{
	}
	CCollision(const CCollision& other)
		: mCollide(other.mCollide)
		, mDistance(other.mDistance)
		, mNormal(other.mNormal)
	{
	}
	CCollision(const CCollision&& other) noexcept
		: mCollide(other.mCollide)
		, mDistance(other.mDistance)
		, mNormal(other.mNormal)
	{
	}
	CCollision& operator=(const CCollision& other)
	{
		mCollide = other.mCollide;
		mDistance = other.mDistance;
		mNormal = other.mNormal;
		return *this;
	}
	CCollision& operator=(const CCollision&& other) noexcept
	{
		mCollide = other.mCollide;
		mDistance = other.mDistance;
		mNormal = other.mNormal;
		return *this;
	}
};
