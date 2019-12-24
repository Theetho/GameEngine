#include "CCollider.h"

CCollider::CCollider(
	CGameObject& gameObject,
	sf::Vector2f center,
	sf::Vector2f bounds
)
	: mGameObject(gameObject)
	, mCenter(center)
	, mBounds(bounds)
	, mOffset(center - gameObject.GetPosition())
{
}

CCollider::~CCollider()
{
}

void CCollider::OnUdpate(const double& delta)
{
	mCenter = mGameObject.GetPosition() + mOffset;
}

void CCollider::OnCollisionEnter(const CCollision& collision)
{
	if (mRigidBody)
	{
		mGameObject.SetPosition(mGameObject.GetPosition() - collision.mNormal);
		mRigidBody->SetVelocity(- Reflect(mRigidBody->GetVelocity(), collision.mNormal) * 0.5f);
	}
}

void CCollider::OnCollisionStay(const CCollision& collision)
{
	OnCollisionEnter(collision);
}

void CCollider::OnCollisionExit()
{
}

const sf::Vector2f& CCollider::GetCenter() const
{
	return mCenter;
}

void CCollider::AttachRigidBody(CRigidBody* rigidBody)
{
	mRigidBody = rigidBody;
}

