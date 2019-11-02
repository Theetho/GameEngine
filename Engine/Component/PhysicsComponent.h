#pragma once

#include "Component.h"
#include "GameObject/Transform.h"

namespace Engine
{
	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent(
			GameObject* owner = nullptr
		);
		~PhysicsComponent();

		void onUpdate(
			const double& delta
		);
		
		inline std::string getName()
		{
			return "Physics";
		}

		inline float getGravity() const
		{
			return m_percentage.gravity * s_force.gravity;
		}

		inline float getFriction() const
		{
			return m_percentage.friction * s_force.friction;
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

		inline bool isJumping() const
		{
			if (m_transform)
				return m_transform->getPosition().y > s_groundLevel;
			return false;
		}
	private:
		Transform* m_transform;
		static const float s_groundLevel;
		
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
		// the GameObject is subjected to
		Force m_percentage;
		
		struct Jump
		{
			bool		 isJumping;
			const float	 jumpStrengh  = 5.0f;
			const double jumpDuration = 0.2;
			double		 delta;
		};
		Jump m_jump;
		
	};
}

