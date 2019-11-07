#include "EnginePch.h"
#include "ColliderComponent.h"
#include "GameObject/GameObject.h"

namespace Engine
{

/// Abstrat base class

	Collider::Collider(
		GameObject& owner,
		const Vec3& center
	)
		: Component(owner)
		, m_center(center)
		, m_offset(center - owner.getTransform().getPosition())
	{}

	Collider::Collider(const Collider & other)
		: Component(other.m_owner)
		, m_center(other.m_center)
		, m_offset(other.m_offset)
	{
	}

	Collider::Collider(const Collider&& other) noexcept
		: Component(other.m_owner)
		, m_center(other.m_center)
		, m_offset(other.m_offset)
	{
	}

	Collider& Collider::operator=(const Collider& other)
	{
		m_owner = other.m_owner;
		m_center = other.m_center;

		return *this;
	}

	Collider& Collider::operator=(const Collider&& other) noexcept
	{
		m_owner = other.m_owner;
		m_center = other.m_center;

		return *this;
	}

	void Collider::onUpdate(
		const double& delta
	)
	{
		m_center = m_owner.getTransform().getPosition() + m_offset;
	}
}