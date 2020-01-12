#include "EnginePch.h"
#include "Transform.h"

namespace Engine
{
	Transform::Transform(const Vec3& position, const Vec3& rotation, const Vec3& scale)
		: mPosition(position)
		, mRotation(rotation)
		, mScale(scale)
		, mModel()
	{
		UpdateModel();
	}

	Transform::Transform(const Transform& transform)
		: mPosition(transform.mPosition)
		, mRotation(transform.mRotation)
		, mScale(transform.mScale)
		, mModel(transform.mModel)
	{}

	Transform::Transform(const Transform&& transform) noexcept
		: mPosition(transform.mPosition)
		, mRotation(transform.mRotation)
		, mScale(transform.mScale)
		, mModel(transform.mModel)
	{}

	Transform& Transform::operator=(const Transform& transform)
	{
		mPosition = transform.mPosition;
		mRotation = transform.mRotation;
		mScale    = transform.mScale;
		mModel    = transform.mModel;

		return *this;
	}

	Transform& Transform::operator=(const Transform&& transform) noexcept
	{
		mPosition = transform.mPosition;
		mRotation = transform.mRotation;
		mScale    = transform.mScale;
		mModel    = transform.mModel;

		return *this;
	}

	Transform::~Transform()
	{
	}

	void Transform::UpdateModel()
	{
		mModel = Matrix::Model(mPosition, mRotation, mScale);
	}

	Vec3& Transform::GetPosition()
	{
		return mPosition;
	}

	Vec3& Transform::GetRotation()
	{
		return mRotation;
	}

	Vec3& Transform::GetScale()
	{
		return mScale;
	}

	const Mat4& Transform::GetModel() const
	{
		return mModel;
	}

	const Vec3& Transform::GetPosition() const
	{
		return mPosition;
	}

	const Vec3& Transform::GetRotation() const
	{
		return mRotation;
	}

	const Vec3& Transform::GetScale() const
	{
		return mScale;
	}

	void Transform::SetPosition(const Vec3& position)
	{
		mPosition = position;
		UpdateModel();
	}

	void Transform::SetRotation(const Vec3& rotation)
	{
		mRotation = rotation;
		UpdateModel();
	}

	void Transform::SetScale(const Vec3& scale)
	{
		mScale = scale;
		UpdateModel();
	}

	void Transform::SetScale(float scale)
	{
		SetScale(Vec3(scale));
	}
}