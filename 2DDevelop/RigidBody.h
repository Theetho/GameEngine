#pragma once

#include "GameObject.h"

class RigidBody
{
public:
	RigidBody(
		GameObject& gameObject
	);
	~RigidBody();
private:
	friend class PhysicsEngine;
	GameObject& mGameObject;
	sf::Vector2f mVelocity;
};

