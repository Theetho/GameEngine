#include "EnginePch.h"
#include "ColliderComponent.h"
#include "GameObject/GameObject.h"

namespace Engine
{

/// Abstrat base class

	Collider::Collider(
		GameObject* owner,
		const Vec3& center
	)
		: Component(owner)
		, m_center(center)
		, m_offset(center - owner->getTransform().getPosition())
	{}

	void Collider::onUpdate(
		const double& delta
	)
	{
		m_center = m_owner->getTransform().getPosition() + m_offset;
	}

/// Box collider

	BoxCollider::BoxCollider(
		GameObject* owner,
		const Vec3& center,
		const float& width,
		const float& height,
		const float& depth
	)
		: Collider(owner, center)
		, m_max(Vec3( width,  height,  depth) / 2.0f)
		, m_min(Vec3(-width, -height, -depth) / 2.0f)
	{
	}

	BoxCollider::~BoxCollider()
	{
	}

/// Sphere collider

	SphereCollider::SphereCollider(
		GameObject* owner,
		const Vec3& center,
		const float& radius
	)
		: Collider(owner, center)
		, m_radius(radius)
	{
	}

	SphereCollider::~SphereCollider()
	{
	}

/// Point collider

	PointCollider::PointCollider(
		GameObject* owner,
		const Vec3& center
	)
		: Collider(owner, center)
	{
	}

	PointCollider::~PointCollider()
	{
	}
}