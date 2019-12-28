#include "EnginePch.h"
#include "SphereCollider.h"
#include "System/CollisionSystem.h"

namespace Engine
{
	SphereCollider::SphereCollider(GameObject& game_object, const Vec3& center, float radius)
		: Collider(game_object, center)
		, mRadius(radius)
	{
		CollisionSystem::AddCollider<SphereCollider>(this);
	}

	SphereCollider::SphereCollider(const SphereCollider& sphere_collider)
		: Collider(sphere_collider.mGameObject, sphere_collider.mCenter)
		, mRadius(sphere_collider.mRadius)
	{
		CollisionSystem::AddCollider<SphereCollider>(this);
	}

	SphereCollider::SphereCollider(const SphereCollider&& sphere_collider) noexcept
		: Collider(sphere_collider.mGameObject, sphere_collider.mCenter)
		, mRadius(sphere_collider.mRadius)
	{
		CollisionSystem::AddCollider<SphereCollider>(this);
	}

	SphereCollider& SphereCollider::operator=(const SphereCollider& sphere_collider)
	{
		*this = SphereCollider(sphere_collider);

		CollisionSystem::AddCollider<SphereCollider>(this);
		
		return *this;
	}

	SphereCollider& SphereCollider::operator=(const SphereCollider&& sphere_collider) noexcept
	{
		*this = SphereCollider(sphere_collider);

		CollisionSystem::AddCollider<SphereCollider>(this);
		
		return *this;
	}

	SphereCollider::~SphereCollider()
	{
		CollisionSystem::RemoveCollider(this);
	}

	float SphereCollider::GetRadius() const
	{
		return mRadius;
	}

	const Vec3& SphereCollider::GetMax() const
	{
		return mCenter + Vec3(mRadius, mRadius, mRadius);
	}
	
	const Vec3& SphereCollider::GetMin() const
	{
		return mCenter - Vec3(mRadius, mRadius, mRadius);
	}

	void SphereCollider::SetScale(float scale)
	{
		mRadius *= scale;
	}
}	