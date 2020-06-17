#pragma once

#include "Camera3D.h"

namespace Engine
{
	class Camera : public Camera3D
	{
	public:
		Camera();
		virtual ~Camera();

		void OnUpdate(const double& delta) override;
		void OnEvent(Event& event) override;
	private:
		// Smooth are used to create smoother rotation and translation
		// with the camera.
		struct SmoothMovement
		{
			SmoothVec3 position = SmoothVec3(Vec3(0), Vec3(10));
			SmoothVec3 target = SmoothVec3(Vec3(0), Vec3(10));
		};

		Vec3 mTarget = Vec3();
		SmoothFloat mSmoothPitch = SmoothFloat(10, 10);
		SmoothFloat mAngleAroundTarget = SmoothFloat(0, 10);
		SmoothFloat mDistanceAroundTarget = SmoothFloat(10, 5);
		SmoothMovement mMovement = SmoothMovement();

		/**
		 * Calculate the position of the camera depending on its pitch and yaw.
	     */
		void CalculateCameraPosition();

		/**
		 * @return The horizontal distance of the camera from the target.
		 */
		inline float CalculateHorizontalDistance()
		{
			return mDistanceAroundTarget * std::cos(glm::radians((float)mSmoothPitch));
		}

		/**
		 * @return The height of the camera from the target.
		 */
		inline float CalculateVerticalDistance()
		{
			return mDistanceAroundTarget * std::sin(glm::radians((float)mSmoothPitch));
		}

		/**
		 * Calculate the pitch and change the pitch if the user is moving the mouse
		 * up or down with the MMB pressed.
		 */
		void CalculatePitch(const double& delta);

		/**
		 * Calculate the yaw around the target. Changes the yaw when the user
		 * moves the mouse horizontally with the MMB pressed.
		 */
		void CalculateAngleAroundPlayer(const double& delta);

		/**
		 * Calculate the distance and the movement of the camera.
		 */
		void CalculateDistance(const double& delta);

		/**
		 * Calculate the position of the camera and its target when the user
		 * moves the mouse with LSHIFT and MMB pressed.
		 */
		void CalculateTarget();
	};
}

