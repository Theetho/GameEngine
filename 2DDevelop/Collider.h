#pragma once

#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "RigidBody.h"

class Collider
{
public:
	Collider(GameObject& gameObject, sf::Vector2f center, sf::Vector2f bounds);
	~Collider();

	virtual void OnUdpate(const double& delta);
	virtual sf::Vector2f GetPointOnBounds(const sf::Vector2f& direction) = 0;
	void AttachRigidBody(RigidBody* rigidBody);
protected:
	friend class PhysicsEngine;
	GameObject& mGameObject;
	RigidBody* mRigidBody = nullptr;
	sf::Vector2f mCenter;
	sf::Vector2f mOffset;
	sf::Vector2f mBounds;
};

