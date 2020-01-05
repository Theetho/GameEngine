#include "EnginePch.h"
#include "RigidBody.h"
#include "./Collider.h"
#include "GameObject/GameObject.h"

namespace Engine
{
	RigidBody::RigidBody(GameObject& game_object)
		: Component(game_object)
		, mTransform(game_object.GetTransform())
		, mVelocity(0.0f)
	{
		auto box    = std::dynamic_pointer_cast<Collider>(game_object.GetComponent<BoxCollider>());
		auto sphere = std::dynamic_pointer_cast<Collider>(game_object.GetComponent<SphereCollider>());
		if (box)
			box->AttachRigidBody();
		if (sphere)
			sphere->AttachRigidBody();
	}

	RigidBody::~RigidBody()
	{}

	void RigidBody::SetUseGravity(bool use)
	{
		mUseGravity = use;
	}

	void RigidBody::SetGroundLevel(float value)
	{
		mGroundLevel = value;
	}

	bool RigidBody::IsUsingGravity() const
	{
		return mUseGravity;
	}

	const Vec3& RigidBody::GetVelocity() const
	{
		return mVelocity;
	}

	float RigidBody::GetGroundLevel() const
	{
		return mGroundLevel;
	}

	Vec3& RigidBody::GetVelocity()
	{
		return mVelocity;
	}

	void RigidBody::OnUpdate(const double& delta)
	{
		Vec3& position = mTransform.GetPosition();
		position += mVelocity;
		
		mTransform.UpdateModel();
	}
}