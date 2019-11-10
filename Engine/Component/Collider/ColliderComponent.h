#pragma once

#include "Component/Component.h"
#include "GameObject/GameObject.h"
#include "Renderer/VertexArray.h"
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

		inline const Vec3& getCenter() const
		{
			return m_center;
		}

		inline virtual const Vec3& getMax() const = 0;

		inline virtual const Vec3& getMin() const = 0;

	protected:
		Vec3 m_center;
		Vec3 m_offset;
	};
}