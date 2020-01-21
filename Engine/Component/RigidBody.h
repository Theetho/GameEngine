#pragma once

#include "Component.h"

namespace Engine
{
	class Transform;
	class CollisionSystem;

	class RigidBody : public Component
	{
	public:
		RigidBody(GameObject& game_object);

		~RigidBody();
		
		void OnUpdate(const double& delta) override;

		bool			  IsUsingGravity() const;
		Vec3&			  GetVelocity();
		const Vec3&		  GetVelocity() const;
		Vec3&			  GetAngularVelocity();
		const Vec3&		  GetAngularVelocity() const;
		Transform&		  GetTransform();
		const Transform&  GetTransform() const;
		float			  GetGroundLevel() const;
		
		void SetUseGravity(bool use);
		void SetGroundLevel(float level);
	private:
		friend class Engine::CollisionSystem;
		bool	   mUseGravity  = true;
		bool	   mIsKinematic = false;
		float	   mMass        = 1.0f;
		float	   mGroundLevel = -1000.0f;
		struct Velocity
		{
			Vec3 regular;
			Vec3 angular;
		};
		Velocity mVelocity;
		Transform& mTransform;
	};
}

