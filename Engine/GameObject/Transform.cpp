#include "EnginePch.h"
#include "Transform.h"
#include "Util/Matrix.h"

namespace Engine
{
	Transform::Transform(
		const Vec3& position,
		const Vec3& rotation,
		const Vec3& scale
	)
		: m_position(position)
		, m_rotation(rotation)
		, m_scale(scale)
		, m_model()
	{
		updateModel();
	}

	Transform::Transform(const Transform& other)
		: m_position(other.m_position)
		, m_rotation(other.m_rotation)
		, m_scale(other.m_scale)
		, m_model(other.m_model)
	{
	}

	Transform::Transform(const Transform&& other) noexcept
		: m_position(other.m_position)
		, m_rotation(other.m_rotation)
		, m_scale(other.m_scale)
		, m_model(other.m_model)
	{
	}

	Transform& Transform::operator=(const Transform& other)
	{
		m_position = other.m_position;
		m_rotation = other.m_rotation;
		m_scale    = other.m_scale;
		m_model    = other.m_model;

		return *this;
	}

	Transform& Transform::operator=(const Transform&& other) noexcept
	{
		m_position = other.m_position;
		m_rotation = other.m_rotation;
		m_scale    = other.m_scale;
		m_model    = other.m_model;

		return *this;
	}

	Transform::~Transform()
	{
	}
}