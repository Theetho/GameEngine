#include "EnginePch.h"
#include "ColliderComponent.h"

namespace Engine
{
	BoxCollider::BoxCollider(
		const Vec3& center,
		const Vec3& boundaries
	)
		: Collider(center)
		, m_boundaries(boundaries)
	{
	}

	SphereCollider::SphereCollider(
		const Vec3& center,
		const float& radius
	)
		: Collider(center)
		, m_radius(radius)
	{
		m_length = m_radius;
	}
}
