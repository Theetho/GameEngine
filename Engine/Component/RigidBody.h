#pragma once

#include "Component.h"

namespace Engine
{
	class Transform;

	class RigidBody : public Component
	{
	public:
		RigidBody(GameObject& game_object);

		~RigidBody();
		
		void OnUpdate(const double& delta) override;

		bool		IsUsingGravity() const;
		Vec3&		GetVelocity();
		const Vec3& GetVelocity() const;
		float		GetGroundLevel() const;
		
		void SetUseGravity(bool use);
		void SetGroundLevel(float value);
	private:
		bool	   mUseGravity  = true;
		bool	   mIsKinematic = false;
		float	   mMass        = 1.0f;
		float	   mGroundLevel = 0.0f;
		Vec3	   mVelocity;
		Transform& mTransform;

	};
}

