#pragma once

#include "SFML/Graphics.hpp"
#include "CCollision.h"

class CCollider;
class CRigidBody;

class CGameObject
{
public:
	CGameObject(
		const sf::Vector2f& position,
		const sf::Vector2f& rotation = sf::Vector2f(0.0f, 0.0f)
	);
	~CGameObject();

	virtual void OnUpdate(const double& delta);

	virtual CCollider* GetCollider();
	virtual CRigidBody* GetRigidBody();
	virtual const sf::Vector2f& GetPosition() const;
	virtual sf::Vector2f& GetPosition();
	virtual const sf::Vector2f& GetRotation() const;
	virtual sf::Vector2f& GetRotation();
	virtual void SetPosition(const sf::Vector2f& position);
	virtual void AttachRigidBody(CRigidBody* rigidBody);

	// TEMPORARY
	bool mIsColliding = false;

protected:
	sf::Vector2f mPosition;
	sf::Vector2f mRotation;
	CCollider* mCollider = nullptr;
	CRigidBody* mRigidBody = nullptr;
};

