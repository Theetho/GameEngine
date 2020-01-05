#pragma once

#include <unordered_map>
#include "SFML/Graphics.hpp"
#include "CGameObject.h"
#include "CRigidBody.h"
#include "CCollision.h"
#include "CMaths.h"

class CCollider
{
public:
	CCollider(CGameObject& gameObject, sf::Vector2f center, sf::Vector2f bounds);
	~CCollider();

	virtual void OnUdpate(const double& delta);
	virtual void OnCollisionEnter(const CCollision& collision);
	virtual void OnCollisionStay(const CCollision& collision);
	virtual void OnCollisionExit();
	virtual sf::Vector2f GetPointOnBounds(const SRay& velocity) = 0;
	virtual sf::Vector2f GetNormalAtPoint(const sf::Vector2f& point) = 0;
	const sf::Vector2f& GetCenter() const;
	const std::unordered_map<const char*, sf::Vector2f>& GetBounds() const;
	void AttachRigidBody(CRigidBody* rigidBody);
protected:
	friend class CPhysicsEngine;
	CGameObject& mGameObject;
	CRigidBody* mRigidBody = nullptr;
	sf::Vector2f mCenter;
	sf::Vector2f mOffset;
	std::unordered_map<const char*, sf::Vector2f> mBounds = {
		{"Min", {0,0}}, {"Max", {0,0}}
	};
};

