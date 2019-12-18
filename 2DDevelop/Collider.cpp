#include "Collider.h"

Collider::Collider(
	GameObject& gameObject,
	sf::Vector2f center,
	sf::Vector2f bounds
)
	: mGameObject(gameObject)
	, mCenter(center)
	, mBounds(bounds)
	, mOffset(center - gameObject.GetPosition())
{
}

Collider::~Collider()
{
}

void Collider::OnUdpate(const double& delta)
{
	mCenter = mGameObject.GetPosition() + mOffset;
}

void Collider::AttachRigidBody(
	RigidBody* rigidBody
)
{
	mRigidBody = rigidBody;
}

