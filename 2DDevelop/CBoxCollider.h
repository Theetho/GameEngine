#pragma once

#include "CCollider.h"

class CBoxCollider : public CCollider
{
public:
	CBoxCollider(CGameObject& gameObject, sf::Vector2f center, sf::Vector2f bounds);
	~CBoxCollider();

	virtual sf::Vector2f GetPointOnBounds(const SRay& velocity) override;
	virtual sf::Vector2f GetNormalAtPoint(const sf::Vector2f& point) override;
};

