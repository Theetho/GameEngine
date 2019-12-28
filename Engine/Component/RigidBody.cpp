#include "EnginePch.h"
#include "RigidBody.h"

namespace Engine
{
	RigidBody::RigidBody(GameObject& game_object,const Vec3& position)
		: Component(game_object)
		, mPosition(position)
		, mRotation(0.0f)
		, mVelocity(0.0f)
	{}

	RigidBody::~RigidBody()
	{}

	void RigidBody::SetUseGravity(bool use)
	{
		mUseGravity = use;
	}

	bool RigidBody::IsUsingGravity() const
	{
		return mUseGravity;
	}

	const Vec3& RigidBody::GetVelocity() const
	{
		return mVelocity;
	}

	Vec3& RigidBody::GetVelocity()
	{
		return mVelocity;
	}

	void RigidBody::OnUpdate(const double& delta)
	{
	}
}