#include "EnginePch.h"
#include "Camera2D.h"

namespace Engine 
{
	Camera2D::Camera2D(float left, float right, float top, float bottom)
		: mProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
		, mViewMatrix(1.0f)
	{
		mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
	}

	Camera2D::~Camera2D()
	{
	}
	
	void Camera2D::SetView()
	{
		Mat4 transform = glm::translate(Mat4(1.0f), mPosition) * glm::rotate(Mat4(1.0f), glm::radians(mRotation), Vec3(0.f, 0.f, 1.f));
	
		mViewMatrix = glm::inverse(transform);
		mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
	}

	void Camera2D::SetProjection(float left, float right, float top, float bottom)
	{
		mProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
	}
}