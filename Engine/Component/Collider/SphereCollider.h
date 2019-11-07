#pragma once
#include "ColliderComponent.h"

namespace Engine
{
	class SphereCollider : public Collider
	{
	public:
		SphereCollider(
			GameObject& owner,
			const Vec3& center,
			const float& radius
		);

		SphereCollider(
			const SphereCollider& other
		);

		SphereCollider(
			const SphereCollider&& other
		) noexcept;

		SphereCollider& operator=(
			const SphereCollider& other
		);

		SphereCollider& operator=(
			const SphereCollider&& other
		) noexcept;

		~SphereCollider();

		void onUpdate(
			const double& delta
		) override;

		inline const float& getRadius() const
		{
			return m_radius;
		}

	private:
		float m_radius;
	};
}