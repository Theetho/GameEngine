#pragma once

#include "Component/Component.h"
#include "Maths.h"

namespace Engine
{
	class Collider : public Component
	{
	public:
		Collider(
			GameObject& owner,
			const Vec3& center
		);

		Collider(
			const Collider& other
		);

		Collider(
			const Collider&& other
		) noexcept;

		Collider& operator=(
			const Collider& other
		);

		Collider& operator=(
			const Collider&& other
		) noexcept;

		virtual ~Collider()
		{}

		void onUpdate(const double& delta) override;
		
		inline Type getType() override
		{
			return Type::Collider;
		}

		inline const Vec3& getCenter() const
		{
			return m_center;
		}

	protected:
		Vec3 m_center;
		Vec3 m_offset;
	};
}