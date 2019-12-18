#include "EnginePch.h"
#include "SphereCollider.h"
#include "System/CollisionSystem.h"
#include "System/PhysicsEngine.h"

namespace Engine
{
	SphereCollider::SphereCollider(
		GameObject& owner,
		const Vec3& center,
		const float& radius
	)
		: Collider(owner, center)
		, m_radius(radius)
	{
		CollisionSystem::AddCollider<SphereCollider>(this);
		//PhysicsEngine::AddCollider(*this);
	}

	SphereCollider::SphereCollider(
		const SphereCollider& other
	)
		: Collider(other.m_owner, other.m_center)
		, m_radius(other.m_radius)
	{
		CollisionSystem::AddCollider<SphereCollider>(this);
		//PhysicsEngine::AddCollider(*this);
	}

	SphereCollider::SphereCollider(
		const SphereCollider&& other
	) noexcept
		: Collider(other.m_owner, other.m_center)
		, m_radius(other.m_radius)
	{
		CollisionSystem::AddCollider<SphereCollider>(this);
		//PhysicsEngine::AddCollider(*this);
	}

	SphereCollider& SphereCollider::operator=(const SphereCollider& other)
	{
		*this = SphereCollider(other);

		CollisionSystem::AddCollider<SphereCollider>(this);
		//PhysicsEngine::AddCollider(*this);
		
		return *this;
	}

	SphereCollider& SphereCollider::operator=(const SphereCollider&& other) noexcept
	{
		*this = SphereCollider(other);

		CollisionSystem::AddCollider<SphereCollider>(this);
		//PhysicsEngine::AddCollider(*this);
		
		return *this;
	}

	SphereCollider::~SphereCollider()
	{
		CollisionSystem::RemoveCollider(this);
		//PhysicsEngine::RemoveCollider(*this);
	}
}	