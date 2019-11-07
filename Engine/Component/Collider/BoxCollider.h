#pragma once
#include "ColliderComponent.h"

namespace Engine
{
	class BoxCollider : public Collider
	{
	public:
		BoxCollider(
			GameObject& owner,
			const Vec3& center,
			const float& width,
			const float& height,
			const float& depth
		);

		BoxCollider(
			const BoxCollider& other
		);

		BoxCollider(
			const BoxCollider&& other
		) noexcept;
		
		BoxCollider& operator=(
			const BoxCollider& other
		);

		BoxCollider& operator=(
			const BoxCollider&& other
		) noexcept;

		~BoxCollider();

		void onUpdate(
			const double& delta
		) override;

		inline const Vec3& getMax() const
		{
			return m_max;
		}

		inline const Vec3& getMin() const
		{
			return m_min;
		}

	private:
		const float m_width, m_height, m_depth;
		// Top Right Front point (x, y, z) / 2
		Vec3  m_max;
		// Bottom Left Back point (-x, -y, -z) / 2
		Vec3  m_min;
	};
}