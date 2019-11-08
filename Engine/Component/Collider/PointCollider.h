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

		void onUpdate(
			const double& delta
		) override;

		inline Type getType() override
		{
			return Type::PointCollider;
		}

	private:
	};
}
