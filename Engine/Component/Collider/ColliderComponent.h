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

		virtual void onUpdate(
			const double& delta
		) override;

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

	// struct that store data
	// of a collision
	class Collision
	{
	public:
		Collision(
			const bool& collide,
			const float& distanceUpAxis,
			const Collider* c1,
			const Collider* c2
		)
			: m_collide(collide)
			, m_distanceUpAxis(distanceUpAxis)
			, m_colliders({ c1, c2 })
		{}

		inline const bool& doesCollide() const
		{
			return m_collide;
		}
		inline const float& distanceUpAxis() const
		{
			return m_distanceUpAxis;
		}
		inline const std::pair<const Collider*, const Collider*>& getColliders() const
		{
			return m_colliders;
		}

	private:
		// The two colliders that are supposedly colliding
		const std::pair<const Collider*, const Collider*> m_colliders;
		// Boolean to tell whether the two colliders are colliding
		const bool  m_collide;
		// The distance beetween the two colliders on the up axis
		const float m_distanceUpAxis;
	};
}