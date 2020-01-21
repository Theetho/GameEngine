#include "EnginePch.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Include/GameObject.h"


namespace Engine
{
	RigidBody::RigidBody(GameObject& game_object)
		: Component(game_object)
		, mTransform(game_object.GetTransform())
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

	void RigidBody::SetGroundLevel(float level)
	{
		mGroundLevel = level;
	}

	bool RigidBody::IsUsingGravity() const
	{
		return mUseGravity;
	}

	const Vec3& RigidBody::GetVelocity() const
	{
		return mVelocity.regular;
	}

	Vec3& RigidBody::GetAngularVelocity()
	{
		return mVelocity.angular;
	}

	const Vec3& RigidBody::GetAngularVelocity() const
	{
		return mVelocity.angular;
	}

	Transform& RigidBody::GetTransform()
	{
		return mTransform;
	}

	const Transform& RigidBody::GetTransform() const
	{
		return mTransform;
	}

	float RigidBody::GetGroundLevel() const
	{
		return mGroundLevel;
	}

	Vec3& RigidBody::GetVelocity()
	{
		return mVelocity.regular;
	}

	void RigidBody::OnUpdate(const double& delta)
	{
		Vec3& position = mTransform.GetPosition();
		position += mVelocity.regular;
		
		if (position.y < mGroundLevel)
			position.y = mGroundLevel;
		
		Vec3& rotation = mTransform.GetRotation();
		rotation += mVelocity.angular;
		
		mTransform.UpdateModel();
	}
}