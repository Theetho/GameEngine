#pragma once

#include "Component.h"
#include "Include/Maths.h"

namespace Engine
{
	class RigidBody : public Component
	{
	public:
		RigidBody(
			GameObject& owner,
			Vec3 position
		);

		~RigidBody();
		
		void useGravity(
			bool use
		);

	private:
		friend class PhysicsEngine;
		bool m_useGravity  = true;
		bool m_isKinematic = false;
		float m_mass       = 1.0f;

		Vec3 m_position;
		Vec3 m_rotation;
		Vec3 m_velocity;
	};
}

