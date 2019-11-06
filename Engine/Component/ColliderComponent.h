#pragma once

#include "Component/Component.h"
#include "Maths.h"

namespace Engine
{
	class CollisionSystem;

	class Collider : public Component
	{
	public:
		Collider(
			GameObject* owner,
			const Vec3& center
		);

		virtual ~Collider()
		{}

		void onUpdate(const double& delta) override;
		
		inline std::string getName() override
		{
			return "Collider";
		}
	protected:
		Vec3 m_center;
		Vec3 m_offset;
	};

	class BoxCollider : public Collider
	{
	public:
		BoxCollider(
			GameObject* owner,
			const Vec3& center,
			const float& width,
			const float& height,
			const float& depth
		);

		~BoxCollider();

	private:
		friend CollisionSystem;

		// Top Right Front point (x, y, z) / 2
		Vec3  m_max;
		// Bottom Left Back point (-x, -y, -z) / 2
		Vec3  m_min;
	};

	class SphereCollider : public Collider
	{
	public:
		SphereCollider(
			GameObject* owner,
			const Vec3& center,
			const float& radius
		);

		~SphereCollider();

	private:
		friend CollisionSystem;

		float m_radius;
	};

	class PointCollider : public Collider
	{
	public:
		PointCollider(
			GameObject* owner,
			const Vec3& center
		);

		~PointCollider();

	private:
		friend CollisionSystem;
	};
}