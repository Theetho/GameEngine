#include "GameObject.h"

GameObject::GameObject(
	const sf::Vector2f& position,
	const sf::Vector2f& rotation
)
	: mPosition(position)
	, mRotation(rotation)
{
}

GameObject::~GameObject()
{
}

const sf::Vector2f& GameObject::GetPosition() const
{
	return mPosition;
}

sf::Vector2f& GameObject::GetPosition()
{
	return mPosition;
}

const sf::Vector2f& GameObject::GetRotation() const
{
	return mRotation;
}

sf::Vector2f& GameObject::GetRotation()
{
	return mRotation;
}