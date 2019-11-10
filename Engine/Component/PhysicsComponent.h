#pragma once

#include "Component.h"
#include "GameObject/Transform.h"

namespace Engine
{
	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent(
			GameObject& owner
		);
		~PhysicsComponent();

		void onUpdate(
			const double& delta
		);
		
		inline const float& getGravity() const
		{
			return m_percentage.gravity * s_force.gravity;
		}

		inline const float& getGroundLevel () const
		{
			return m_groundLevel;
		}

		inline float getFriction() const
		{
			return m_percentage.friction * s_force.friction;
		}

		inline void setGroundLevel(
			const float& value
		)
		{
			m_groundLevel = value;
		}

		inline void setFrictionPecentage(
			const float& percentage
		)
		{
			m_percentage.friction = percentage;
		}

		inline void jump()
		{
			m_jump.isJumping = true;
		}

		inline bool isInAir() const
		{
			return m_jump.isJumping || m_jump.isFalling;
		}

		inline const bool& isJumping() const
		{
			return m_jump.isJumping;
		}

		inline const bool& isFalling() const
		{
			return m_jump.isFalling;
		}
	private:
		Transform& m_transform;
		float m_groundLevel;
		
		struct Force
		{
			float gravity;
			float friction;

			Force(
				const float& gravity,
				const float& friction
			)
				: gravity(gravity)
				, friction(friction)
			{
			}
		};
		// Value for each force
		static const Force s_force;
		// Percentage of the original force that 
		// are applied to the GameObject
		Force m_percentage;
		
		struct Jump
		{
			bool		 isJumping;
			bool		 isFalling;
			const float	 jumpStrengh  = 10.0f;
			const double jumpDuration = 0.2;
			double		 delta;
		};
		Jump m_jump;
		
	};
}

