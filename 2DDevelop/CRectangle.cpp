#include "CRectangle.h"
#include "CBoxCollider.h"

using namespace sf;

CRectangle::CRectangle(
	const sf::Vector2f& dimension,
	const sf::Vector2f& position,
	const sf::Vector2f& rotation
)
	: CGameObject(position, rotation)
	, RectangleShape(dimension)
{
	setPosition(position - (dimension / 2.0f));
	mCollider = new CBoxCollider(*this, position, dimension / 2.0f);
}

CRectangle::~CRectangle()
{
}

void CRectangle::OnUpdate(const double& delta)
{
	if (mRigidBody)
	{
		mRigidBody->OnUpdate(delta);
		mPosition += mRigidBody->GetVelocity();
		setPosition(mPosition - getSize() / 2.0f);
	}
	mCollider->OnUdpate(delta);
}
