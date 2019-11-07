#include "EnginePch.h"
#include "BoxCollider.h"

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
		, m_max(Vec3(width, height, depth) / 2.0f)
		, m_min(Vec3(-width, -height, -depth) / 2.0f)
	{
	}

	BoxCollider::BoxCollider(
		const BoxCollider& other
	)
		: Collider(other.m_owner, other.m_center)
		, m_max(other.m_max)
		, m_min(other.m_min)
	{
	}

	BoxCollider::BoxCollider(
		const BoxCollider&& other
	) noexcept
		: Collider(other.m_owner, other.m_center)
		, m_max(other.m_max)
		, m_min(other.m_min)
	{
	}

	BoxCollider& BoxCollider::operator=(const BoxCollider& other)
	{
		*this = BoxCollider(other);

		return *this;
	}

	BoxCollider& BoxCollider::operator=(const BoxCollider&& other) noexcept
	{
		*this = BoxCollider(other);

		return *this;
	}

	BoxCollider::~BoxCollider()
	{
	}
}
