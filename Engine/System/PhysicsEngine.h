#pragma once

#include "Include/Component.h"

namespace Engine
{
	class PhysicsEngine
	{
	public:
		PhysicsEngine();
		~PhysicsEngine();

		void onUpdate(
			const double& delta
		);

	private:
		std::vector<RigidBody*>	m_rigidBodies;
		std::vector<Collider*>  m_colliders;

		// CONSTANTS
		float GRAVITATIONAL_ACCELERATION = 9.81f;


		void applyGravity(
			std::vector<RigidBody*>& rigidBodies
		) const;

		void resolveCollisions();

		Collision detectCollision(
			Collider* mainCollider,
			Collider* otherCollider
		) const;
	};
}

