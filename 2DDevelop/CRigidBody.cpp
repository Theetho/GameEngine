#include "CRigidBody.h"

#define SPEED 50.0f
#define MAXSPEED 3.0f

using namespace sf;

CRigidBody::CRigidBody(
	CGameObject& gameObject
)
	: mGameObject(gameObject)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::OnUpdate(const double& delta)
{
	//if (mGameObject.mIsColliding)
	//	return;

	if (Keyboard::isKeyPressed(Keyboard::Z))
	{
		mVelocity.y -= SPEED * delta;
		if (mVelocity.y < - MAXSPEED)
			mVelocity.y = - MAXSPEED;
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		mVelocity.y += SPEED * delta;
		if (mVelocity.y > MAXSPEED)
			mVelocity.y = MAXSPEED;
	}
	if (Keyboard::isKeyPressed(Keyboard::Q))
	{
		mVelocity.x -= SPEED * delta; 
		if (mVelocity.x < - MAXSPEED)
			mVelocity.x = - MAXSPEED;
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		mVelocity.x += SPEED * delta;
		if (mVelocity.x > MAXSPEED)
			mVelocity.x = MAXSPEED;
	}

}

const sf::Vector2f& CRigidBody::GetVelocity() const
{
	return mVelocity;
}

void CRigidBody::SetVelocity(const sf::Vector2f& velocity)
{
	mVelocity = velocity;
}
