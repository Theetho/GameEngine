#pragma once

namespace Engine 
{
	class Camera2D
	{
	public:
		Camera2D(float left, float right, float top, float bottom);
		~Camera2D();

		void SetView();
		void SetProjection(float left, float right, float top, float bottom);
		inline const Mat4& GetProjectionViewMatrix() const
		{
			return mViewProjectionMatrix;
		}
	private:
		Mat4 mProjectionMatrix;
		Mat4 mViewMatrix;
		Mat4 mViewProjectionMatrix;

		Vec3 mPosition;
		float mRotation;
	};
}

