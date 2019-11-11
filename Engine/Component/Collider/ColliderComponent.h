#pragma once

#include "Component/Component.h"
#include "GameObject/GameObject.h"
#include "Renderer/VertexArray.h"
#include "Maths.h"

namespace Engine
{
	// struct that store data
	// of a collision
	class Collision
	{
	public:
		Collision(
			const bool& collide,
			const float& distance
		)
			: m_collide(collide)
			, m_distance(distance)
		{ }

		inline const bool& doesCollide() const
		{
			return m_collide;
		}
		inline const float& distance() const
		{
			return m_distance;
		}
	private:
		bool  m_collide;
		float m_distance;
	};

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