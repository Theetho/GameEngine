#pragma once

#include "Core/Scene/SceneObject.h"
#include "Core/Event.h"
#include "Util/Matrix.h"

namespace Engine
{
	class Camera3D : public SceneObject
	{
	public:
		struct Sensitivity
		{
			float pitch = 0.025f;
			float yaw = 0.025f;
			float roll = 0.025f;
		};

		Camera3D(const Vec3& position);
		~Camera3D();

		inline virtual const Vec3& GetPosition() const
		{
			return mPosition;
		}
		inline virtual float GetPitch() const
		{
			return mPitch;
		}
		inline virtual float GetYaw() const
		{
			return mYaw;
		}
		inline virtual float GetRoll() const
		{
			return mRoll;
		}
		inline virtual float GetNear() const
		{
			return mNear;
		}
		inline virtual float GetFar() const
		{
			return mFar;
		}
		inline virtual float GetAspectRatio() const
		{
			return mAspectRatio;
		}
		inline virtual float GetFov() const
		{
			return mFov;
		}
		inline virtual const Mat4& GetViewMatrix() const
		{
			return mViewMatrix;
		}
		inline virtual const Mat4& GetProjectionMatrix() const
		{
			return mProjectionMatrix;
		}
		inline virtual const Mat4& GetProjectionViewMatrix() const
		{
			return mProjectionMatrix * mViewMatrix;
		}
	
		inline virtual void SetPosition(const Vec3& position)
		{
			mPosition = position;
		}

		void virtual OnUpdate(const double& delta);
		void virtual OnEvent(Event& event);

		virtual inline void UpdateViewMatrix()
		{
			mViewMatrix = Matrix::View(this);
		}

		void Rotate(const Vec2& offset);
		void ReverseOnUpAxis(const Vec3& position);
	protected:
		Sensitivity mSensitivity;

		Vec3 mPosition;

		Mat4 mProjectionMatrix;
		Mat4 mViewMatrix = Mat4();

		float mPitch, mYaw, mRoll;
		float mNear = 0.2f, mFar = 400.0f, mAspectRatio = 16.0f/9.0f, mFov = 70.0f;
		static const float MAX_PITCH, MAX_YAW, MAX_ROLL;

		virtual inline void UpdateProjectionMatrix()
		{
			mProjectionMatrix = Matrix::Projection(mFov, mAspectRatio, mNear, mFar);
		}

		inline void ClampPitch()
		{
			if (mPitch > MAX_PITCH)		   mPitch = MAX_PITCH;
			else if (mPitch < - MAX_PITCH) mPitch = - MAX_PITCH;
		}
		inline void ClampYaw()
		{
			if (mYaw < 0.0f)		 mYaw += MAX_YAW;
			else if (mYaw > MAX_YAW) mYaw -= MAX_YAW;
		}

		inline void OnUiSelected() override
		{
			if (ImGui::CollapsingHeader(ApplyID("Camera"), ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Text("Position");
				ImGui::DragFloat3(ApplyID("##Position"), (float*)(&mPosition), 0.1f);
				ImGui::Text("Angles");
				ImGui::SliderFloat(ApplyID("Pitch"), &mPitch, -MAX_PITCH, MAX_PITCH);
				ImGui::SliderFloat(ApplyID("Yaw"), &mYaw, -MAX_YAW, MAX_YAW);
				ImGui::SliderFloat(ApplyID("Roll"), &mRoll, -MAX_PITCH, MAX_PITCH);
				ImGui::Text("Sensitivity");
				ImGui::DragFloat2(ApplyID("##Sensitivity"), (float*)&mSensitivity, 0.01f);
				ImGui::DragFloat(ApplyID("Near"), &mNear, 0.1f, 0.1f, mFar);
				ImGui::DragFloat(ApplyID("Far"), &mFar, 100.0f, mNear, 10000.0f);
				ImGui::DragFloat(ApplyID("FOV"), &mFov, 1.0f, 1.0f, 360.0f);
			}
		}
	};
}

