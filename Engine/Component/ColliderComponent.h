#pragma once

#include "Maths.h"

namespace Engine
{
	template<unsigned int dimension>
	class Collider
	{
		using Vec = glm::vec<dimension, float>;
	public:
		Collider(
			const Vec& center
		)
			: m_center(center)
		{
		}

		virtual ~Collider()
		{
		}

		template<unsigned int dim>
		bool collide(
			const Collider* other
		)
		{
			float distance = glm::distance(m_center, other->m_center);
			float distanceMin = m_length + m_center->m_length;

			if (distance <= distanceMin)
				return true;
			return false;
		}

	protected:
		Vec   m_center;
		float m_length;
	};

	class BoxCollider : public Collider<3>
	{
	public:
		BoxCollider(
			const Vec3& center,
			const Vec3& boundaries
		);

		~BoxCollider()
		{
		}
	private:
		Vec3 m_boundaries;
	};
	
	class SphereCollider : public Collider<3>
	{
	public:
		SphereCollider(
			const Vec3& center,
			const float& radius
		);
		~SphereCollider()
		{
		}
	private:
		float m_radius;
	};
	
	class RectangleCollider : public Collider<2>
	{
	};
	
	class CircleCollider : public Collider<2>
	{
	};
	
	template<unsigned int dimension>
	class PointCollider : public Collider<dimension>
	{
	};
}