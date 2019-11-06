#pragma once

#include "Component.h"
#include "GameObject/Transform.h"

namespace Engine
{
	class MovementComponent : public Component
	{
	public:
		MovementComponent(
			GameObject* owner
		);
		~MovementComponent();

		void onUpdate(
			const double& delta
		) override;
		
		std::string getName() override
		{
			return "Movement";
		}
		
		inline const Vec3& getDirection() const
		{
			return m_movement.direction;
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
			const float rotation = 200.0f;
			const float max		 = 5.0f;
			float forward;
			float strafe;
		};
		Speed m_speed;

		struct Movement
		{
			bool forward;
			bool strafe;
			Vec3 direction;

			inline void reset()
			{
				forward   = false;
				strafe    = false;
				direction = Vec3(0.0f, 0.0f, 0.0f);
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

		struct Axis
		{
			Vec3 up = Vec3(0.0, 1.0, 0.0);
			Vec3 forward = Vec3(0.0, 0.0, 1.0);
			Vec3 strafe;
		};
		Axis m_axis;

		void clapSpeed(
			float& speed,
			const float& friction,
			const bool& moving
		);
	};
}

