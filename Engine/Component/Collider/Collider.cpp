#include "EnginePch.h"
#include "Collider.h"
#include "Core/Log.h"

namespace Engine
{

/// Abstrat base class

	Collider::Collider(GameObject& game_object, const Vec3& center)
		: Component(game_object)
		, mCenter(center)
		, mOffset(center - game_object.GetTransform().GetPosition())
	{}

	Collider::Collider(const Collider & collider)
		: Component(collider.mGameObject)
		, mCenter(collider.mCenter)
		, mOffset(collider.mOffset)
	{}

	Collider::Collider(const Collider&& collider) noexcept
		: Component(collider.mGameObject)
		, mCenter(collider.mCenter)
		, mOffset(collider.mOffset)
	{}

	Collider& Collider::operator=(const Collider& collider)
	{
		mGameObject = collider.mGameObject;
		mCenter = collider.mCenter;

		return *this;
	}

	Collider& Collider::operator=(const Collider&& collider) noexcept
	{
		mGameObject = collider.mGameObject;
		mCenter = collider.mCenter;

		return *this;
	}
	
	Collider::~Collider()
	{}

	void Collider::OnUpdate(const double& delta)
	{
		mCenter = mGameObject.GetTransform().GetPosition() + mOffset;
	}

	void Collider::AttachRigidBody(RigidBody* rigid_body)
	{
		mRigidBody = rigid_body;
	}
	
	const Vec3& Collider::GetCenter() const
	{
		return mCenter;
	}
	
	const RigidBody* Collider::GetRigidBody() const
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