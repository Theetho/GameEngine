#pragma once

#include "CCollider.h"

class CSphereCollider : public CCollider
{
public:
	CSphereCollider(CGameObject& gameObject, sf::Vector2f center, sf::Vector2f bounds);
	~CSphereCollider();

	virtual sf::Vector2f GetPointOnBounds(const SRay& velocity) override;
	virtual sf::Vector2f GetNormalAtPoint(const sf::Vector2f& point) override;
};

