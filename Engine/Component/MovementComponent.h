#pragma once

#include "Component.h"
#include "GameObject/Transform.h"

namespace Engine
{
	class MovementComponent : public Component
	{
	public:
		MovementComponent(
			GameObject* owner = nullptr
		);
		~MovementComponent();

		void onUpdate(
			const double& delta
		) override;
		
		std::string getName() override
		{
			return "Movement";
		}
		
		inline bool isMoving() const
		{
			return m_movement.forward || m_movement.strafe;
		}

	private:
		Transform* m_transform;

		struct Speed
		{
			const float velocity = 0.1f;
			const float rotation = 150.0f;
			const float max		 = 5.0f;
			float forward;
			float strafe;
		};
		Speed m_speed;

		struct Movement
		{
			bool  forward;
			bool  strafe;
			float dx;
			float dy;
			float dz;

			inline void reset()
			{
				forward  = false;
				strafe   = false;
				dx		 = 0.0f;
				dy		 = 0.0f;
				dz		 = 0.0f;
			}
		};
		Movement m_movement;

		struct Distance
		{
			float forward;
			float strafe;

			inline void reset()
			{
				forward  = 0.0f;
				strafe = 0.0f;
			}
		};
		Distance m_distance;

		void clapSpeed(
			float& speed,
			const float& friction,
			const bool& moving
		);
	};
}

