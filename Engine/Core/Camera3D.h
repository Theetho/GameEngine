#pragma once

#include "Include/Maths.h"
#include "Event.h"
#include "Input.h"

namespace Engine
{
	class GameObject;

	class Camera3D
	{
	public:
		Camera3D(
			const Vec3& position = Vec3(0.0f, 1.0f, 0.0f)
		);

		virtual ~Camera3D();

		virtual void onUpdate(
			const double& delta
		);

		virtual void onEvent(
			Event& event
		);

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

		inline const float& getPitch() const
		{
			return m_angle.pitch;
		}

		inline const float& getYaw() const
		{
			return m_angle.yaw;
		}

		inline const float& getRoll() const
		{
			return m_angle.roll;
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

	protected:
		Mat4 m_view;
		Mat4 m_projection;
		Mat4 m_VP;

		Vec3 m_position;

		struct EulerAngle
		{
			float pitch;
			float yaw;
			float roll;
		};
		EulerAngle m_angle;

		void updateVP();

		inline void calculatePitch()
		{
			if (Input::isMouseButtonPressed(ENGINE_MOUSE_BUTTON_RIGHT))
			{
				m_angle.pitch -= Input::getMouseOffset().y * 0.05f;

				if (m_angle.pitch > 89.f)
					m_angle.pitch = 89.f;
				else if (m_angle.pitch < 0.f)
					m_angle.pitch = 0.f;
			}
		}
	};

	class Camera3DLocked : public Camera3D
	{
	public:
		Camera3DLocked(
			const GameObject& target,
			const float& distance = 6.0f
		);
		virtual ~Camera3DLocked();

		virtual void onUpdate(
			const double& delta
		) override;

		virtual void onEvent(
			Event& event
		) override;

	protected:
		const GameObject& m_target;

		float m_distance;
		float m_angleAroundTarget;

		virtual float calculateHorizontalDistance();
		virtual float calculateVerticalDistance();
		virtual void  calculateCameraPosition();
		virtual void  calculateZoom();
		virtual void  calculateAngleAroundPlayer();
	};
}

