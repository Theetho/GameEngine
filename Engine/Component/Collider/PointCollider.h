#pragma once
#include "ColliderComponent.h"

namespace Engine
{
	class PointCollider : public Collider
	{
	public:
		PointCollider(
			GameObject& owner,
			const Vec3& center
		);

		PointCollider(
			const PointCollider& other
		);

		PointCollider(
			const PointCollider&& other
		) noexcept;

		PointCollider& operator=(
			const PointCollider& other
		);

		PointCollider& operator=(
			const PointCollider&& other
		) noexcept;

		~PointCollider();

		inline const Vec3& getMax() const override
		{
			return m_center;
		}

		inline const Vec3& getMin() const override
		{
			return m_center;
		}
	};
}
