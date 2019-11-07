#include "EnginePch.h"
#include "PointCollider.h"

namespace Engine
{
	PointCollider::PointCollider(
		GameObject& owner,
		const Vec3& center
	)
		: Collider(owner, center)
	{
	}

	PointCollider::PointCollider(
		const PointCollider& other
	)
		: Collider(other.m_owner, other.m_center)
	{
	}

	PointCollider::PointCollider(
		const PointCollider&& other
	) noexcept
		: Collider(other.m_owner, other.m_center)
	{
	}

	PointCollider& PointCollider::operator=(const PointCollider& other)
	{
		*this = PointCollider(other);

		return *this;
	}

	PointCollider& PointCollider::operator=(const PointCollider&& other) noexcept
	{
		*this = PointCollider(other);

		return *this;
	}

	PointCollider::~PointCollider()
	{
	}
}