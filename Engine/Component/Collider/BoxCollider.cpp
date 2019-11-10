#include "EnginePch.h"
#include "BoxCollider.h"
#include "System/CollisionSystem.h"

namespace Engine
{
	BoxCollider::BoxCollider(
		GameObject& owner,
		const Vec3& center,
		const float& width,
		const float& height,
		const float& depth
	)
		: Collider(owner, center)
		, m_width(width / 2.0f)
		, m_height(height / 2.0f)
		, m_depth(depth / 2.0f)
		, m_max(center + Vec3(m_width, m_height, m_depth))
		, m_min(center - Vec3(m_width, m_height, m_depth))
	{
		CollisionSystem::AddCollider<BoxCollider>(this);
	}

	BoxCollider::BoxCollider(
		const BoxCollider& other
	)
		: Collider(other.m_owner, other.m_center)
		, m_max(other.m_max)
		, m_min(other.m_min)
		, m_width(other.m_width)
		, m_height(other.m_height)
		, m_depth(other.m_depth)
	{
		CollisionSystem::AddCollider<BoxCollider>(this);
	}

	BoxCollider::BoxCollider(
		const BoxCollider&& other
	) noexcept
		: Collider(other.m_owner, other.m_center)
		, m_max(other.m_max)
		, m_min(other.m_min)
		, m_width(other.m_width)
		, m_height(other.m_height)
		, m_depth(other.m_depth)
	{
		CollisionSystem::AddCollider<BoxCollider>(this);
	}

	BoxCollider& BoxCollider::operator=(const BoxCollider& other)
	{
		*this = BoxCollider(other);

		CollisionSystem::AddCollider<BoxCollider>(this);

		return *this;
	}

	BoxCollider& BoxCollider::operator=(const BoxCollider&& other) noexcept
	{
		*this = BoxCollider(other);

		CollisionSystem::AddCollider<BoxCollider>(this);

		return *this;
	}

	BoxCollider::~BoxCollider()
	{
		CollisionSystem::RemoveCollider(this);
	}
	
	void BoxCollider::onUpdate(const double& delta)
	{
		if (m_owner.isMoveable())
		{
			m_center = m_owner.getTransform().getPosition() + m_offset;
			m_max    = m_center + Vec3(m_width, m_height, m_depth);
			m_min	 = m_center - Vec3(m_width, m_height, m_depth);
		}
	}
}
