#pragma once
#include "Collider.h"

namespace Engine
{
	class SphereCollider : public Collider
	{
	public:
		SphereCollider(GameObject& game_object, const Vec3& center, float radius);
		SphereCollider(const SphereCollider& sphere_collider);
		SphereCollider(const SphereCollider&& sphere_collider) noexcept;
		SphereCollider& operator=(const SphereCollider& sphere_collider);
		SphereCollider& operator=(const SphereCollider&& sphere_collider) noexcept;
		~SphereCollider();

		float		GetRadius() const;
		const Vec3& GetMax() const override;
		const Vec3& GetMin() const override;

		void SetScale(float scale);
	private:
		float mRadius;
	};
}