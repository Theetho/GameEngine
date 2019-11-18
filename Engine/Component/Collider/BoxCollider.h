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

		inline const Vec3& getMax() const override
		{
			return m_max;
		}

		inline const Vec3& getMin() const override
		{
			return m_min;
		}

		inline void setScale(
			const Vec3& scale
		)
		{
			m_width  *= scale.x;
			m_height *= scale.y;
			m_depth  *= scale.z;
		}

		inline void setScale(
			const float& scale
		)
		{
			setScale(Vec3(scale));
		}

	private:
		float m_width, m_height, m_depth;
		// Top Right Front point (width, height, depth) / 2
		Vec3  m_max;
		// Bottom Left Back point (-width, -height, - depth) / 2
		Vec3  m_min;
	};
}