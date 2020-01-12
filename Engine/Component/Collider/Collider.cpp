#include "EnginePch.h"
#include "Collider.h"
#include "Include/GameObject.h"
#include "Component/RigidBody.h"


namespace Engine
{
/// Abstrat base class

	Collider::Collider(GameObject& game_object, const Vec3& center)
		: Component(game_object)
		, mCenter(center)
		, mOffset(center - game_object.GetTransform().GetPosition())
		, mRigidBody(game_object.GetComponent<RigidBody>())
	{}

	Collider::Collider(const Collider & collider)
		: Component(collider.mGameObject)
		, mCenter(collider.mCenter)
		, mOffset(collider.mOffset)
		, mRigidBody(collider.mRigidBody)
	{
	}

	Collider::Collider(const Collider&& collider) noexcept
		: Component(collider.mGameObject)
		, mCenter(collider.mCenter)
		, mOffset(collider.mOffset)
		, mRigidBody(collider.mRigidBody)
	{}

	Collider& Collider::operator=(const Collider& collider)
	{
		mGameObject = collider.mGameObject;
		mOffset		= collider.mOffset;
		mCenter     = collider.mCenter;
		mRigidBody  = collider.mRigidBody;

		return *this;
	}

	Collider& Collider::operator=(const Collider&& collider) noexcept
	{
		mGameObject = collider.mGameObject;
		mOffset		= collider.mOffset;
		mCenter     = collider.mCenter;
		mRigidBody  = collider.mRigidBody;

		return *this;
	}
	
	Collider::~Collider()
	{}

	void Collider::OnUpdate(const double& delta)
	{
		mCenter = mGameObject.GetTransform().GetPosition() + mOffset;
	}

	void Collider::AttachRigidBody()
	{
		mRigidBody = mGameObject.GetComponent<RigidBody>();
		UpdateCollisionSystem();
	}
	
	const Vec3& Collider::GetCenter() const
	{
		return mCenter;
	}

	const Vec3& Collider::GetMax() const
	{
		return Vec3(0.0f);
	}

	const Vec3& Collider::GetMin() const
	{
		return Vec3(0.0f);
	}
	
	const Ref<RigidBody> Collider::GetRigidBody() const
	{
		return mRigidBody;
	}
	
	// Collision class
	
	Collision::Collision(bool collide, float distance_up_axis, const Collider* first, const Collider* second)
		: mIsColliding(collide)
		, mDistanceUpAxis(distance_up_axis)
		, mColliders({ first, second })
	{}

	bool Collision::IsColliding() const
	{
		return mIsColliding;
	}

	float Collision::GetDistanceUpAxis() const
	{
		return mDistanceUpAxis;
	}

	const std::pair<const Collider*, const Collider*>& Collision::GetColliders() const
	{
		return mColliders;
	}
}