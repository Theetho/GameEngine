#pragma once

#include "Component.h"
#include "GameObject/Transform.h"

namespace Engine
{
	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent(GameObject& gameObject);
		~PhysicsComponent();

		void OnUpdate(const double& delta);
		
		float GetGravity() const;
		float GetGroundLevel() const;
		float GetFriction() const;

		bool IsInAir() const;
		bool IsJumping() const;
		bool IsFalling() const;

		void SetGroundLevel(float value);
		void SetFrictionPecentage(float percentage);
		void SetIsJumping();
	private:
		Transform& mTransform;
		float	   mGroundLevel;
		
		struct Force
		{
			float gravity;
			float friction;

			Force(
				float gravity,
				float friction
			)
				: gravity(gravity)
				, friction(friction)
			{}
		};
		// Value for each force
		static const Force sForce;
		// Percentage of the original force that 
		// are applied to the game object
		Force mPercentage;
		
		struct Jump
		{
			bool		 is_jumping;
			bool		 is_falling;
			const float	 jump_strengh  = 10.0f;
			const double jump_duration = 0.2;
			double		 delta;
		};
		Jump m_Jump;
		
	};
}

