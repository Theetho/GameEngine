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
		std::vector<RigidBody*>		 m_rigidBodies;
		std::vector<BoxCollider*>    m_boxColliders;
		std::vector<SphereCollider*> m_sphereColliders;

		// CONSTANTS
		float GRAVITATIONAL_ACCELERATION = 9.81f;


		void applyGravity(
			std::vector<RigidBody*>& rigidBodies
		) const;

		void handleCollision() const;
	};
}

