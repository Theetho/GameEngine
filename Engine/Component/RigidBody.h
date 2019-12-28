#pragma once

#include "Component.h"
#include "Include/Maths.h"

namespace Engine
{
	class RigidBody : public Component
	{
	public:
		RigidBody(GameObject& game_object, const Vec3& position);

		~RigidBody();
		
		void OnUpdate(const double& delta) override;

		bool		IsUsingGravity() const;
		Vec3&		GetVelocity();
		const Vec3& GetVelocity() const;
		
		void SetUseGravity(bool use);
	private:
		bool  mUseGravity  = true;
		bool  mIsKinematic = false;
		float mMass       = 1.0f;
		Vec3  mPosition;
		Vec3  mRotation;
		Vec3  mVelocity;

	};
}

