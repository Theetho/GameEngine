#pragma once

#include "CGameObject.h"

class CRigidBody
{
public:
	CRigidBody(
		CGameObject& gameObject
	);
	~CRigidBody();

	void OnUpdate(const double& delta);

	const sf::Vector2f& GetVelocity() const;
	void SetVelocity(const sf::Vector2f& velocity);
private:
	friend class CPhysicsEngine;
	CGameObject& mGameObject;
	sf::Vector2f mVelocity;
};

