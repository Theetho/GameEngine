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

		inline void setScale(
			const float& scale
		)
		{
			m_radius *= scale;
		}

		inline const float& getRadius() const
		{
			return m_radius;
		}

		inline const Vec3& getMax() const override
		{
			return m_center + Vec3(m_radius, m_radius, m_radius);
		}

		inline const Vec3& getMin() const override
		{
			return m_center - Vec3(m_radius, m_radius, m_radius);
		}

	private:
		float m_radius;
	};
}