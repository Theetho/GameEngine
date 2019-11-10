#include "EnginePch.h"
#include "PointCollider.h"
#include "System/CollisionSystem.h"

namespace Engine
{
	PointCollider::PointCollider(
		GameObject& owner,
		const Vec3& center
	)
		: Collider(owner, center)
	{
		CollisionSystem::AddCollider<PointCollider>(this);
	}

	PointCollider::PointCollider(
		const PointCollider& other
	)
		: Collider(other.m_owner, other.m_center)
	{
		CollisionSystem::AddCollider<PointCollider>(this);
	}

	PointCollider::PointCollider(
		const PointCollider&& other
	) noexcept
		: Collider(other.m_owner, other.m_center)
	{
		CollisionSystem::AddCollider<PointCollider>(this);
	}

	PointCollider& PointCollider::operator=(const PointCollider& other)
	{
		*this = PointCollider(other);

		CollisionSystem::AddCollider<PointCollider>(this);

		return *this;
	}

	PointCollider& PointCollider::operator=(const PointCollider&& other) noexcept
	{
		*this = PointCollider(other);

		CollisionSystem::AddCollider<PointCollider>(this);

		return *this;
	}

	PointCollider::~PointCollider()
	{
		CollisionSystem::RemoveCollider(this);
	}

	void PointCollider::onUpdate(const double& delta)
	{
		m_center = m_owner.getTransform().getPosition() + m_offset;
	}
}