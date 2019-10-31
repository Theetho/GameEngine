#pragma once

#include "Maths.h"
#include "Event.h"

namespace Engine
{
	class CameraController;

	class Camera3D
	{
	public:
		Camera3D(
			const Vec3& position = Vec3(0.0f, 0.0f, 0.0f)
		);

		~Camera3D();

		void onUpdate(
			const double& delta
		);

		void onEvent(
			Event& event
		);

		inline void getControlled(
			const CameraController* controller
		)
		{
			m_controller = controller;
			m_yaw   = 0.0f;
			m_pitch = 60.0f;
		}

		inline void setPosition(
			const Vec3& position
		)
		{
			m_position = position;
		}

		inline const Vec3& getPosition() const
		{
			return m_position;
		}

		inline const float getPitch() const 
		{
			return m_pitch; 
		}

		inline const float getYaw() const
		{ 
			return m_yaw;
		}

		inline const Mat4& getView() const
		{
			return m_view;	
		}
		
		inline const Mat4& getProjection() const
		{
			return m_projection;
		}
		
		inline const Mat4& getVP() const
		{
			return m_VP;
		}

	private:
		Mat4 m_view;
		Mat4 m_projection;
		Mat4 m_VP;

		Vec3 m_position;

		float m_speed, m_mouseSpeed, m_rotationSpeed;
		float m_forwardSpeed, m_strafeSpeed;
		float m_pitch, m_yaw;

		const CameraController* m_controller;

		void updateVP();
	};
}

