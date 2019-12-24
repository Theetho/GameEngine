#include "CGameObject.h"
#include "CCollider.h"

CGameObject::CGameObject(
	const sf::Vector2f& position,
	const sf::Vector2f& rotation
)
	: mPosition(position)
	, mRotation(rotation)
{
}

CGameObject::~CGameObject()
{
	if (mCollider)
		delete mCollider;
}

void CGameObject::OnUpdate(const double& delta)
{
}

CCollider* CGameObject::GetCollider()
{
	return mCollider;
}

CRigidBody* CGameObject::GetRigidBody()
{
	return mRigidBody;
}

const sf::Vector2f& CGameObject::GetPosition() const
{
	return mPosition;
}

sf::Vector2f& CGameObject::GetPosition()
{
	return mPosition;
}

const sf::Vector2f& CGameObject::GetRotation() const
{
	return mRotation;
}

sf::Vector2f& CGameObject::GetRotation()
{
	return mRotation;
}

void CGameObject::SetPosition(const sf::Vector2f& position)
{
	mPosition = position;
}

void CGameObject::AttachRigidBody(CRigidBody* rigidBody)
{
	mRigidBody = rigidBody;
	mCollider->AttachRigidBody(mRigidBody);
}
