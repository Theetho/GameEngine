#include "..\..\2DDevelop\PhysicsEngine.h"
#pragma once

#include "Include/Component.h"

namespace Engine
{
	class PhysicsEngine
	{
	public:
		void onUpdate(
			const double& delta
		);
		static PhysicsEngine* GetInstance()
		{
			return s_instance;
		}

		static inline void AddCollider(
			Collider* collider
		)
		{
			s_instance->m_colliders.push_back(collider);
		}

		static inline void RemoveCollider(
			Collider* collider
		)
		{
			std::remove_if(
				s_instance->m_colliders.begin(),
				s_instance->m_colliders.end(),
				[collider](Collider* mCollider)
				{
					return mCollider == collider;
				}
			);
		}
	private:
		PhysicsEngine();
		~PhysicsEngine();

		static PhysicsEngine* s_instance;

		std::vector<RigidBody*>	m_rigidBodies;
		std::vector<Collider*> m_colliders;
		//std::vector<SphereCollider&> m_colliders;

		// CONSTANTS
		float GRAVITATIONAL_ACCELERATION = 9.81f;


		void applyGravity(
			std::vector<RigidBody*>& rigidBodies
		) const;

		void resolveCollisions();

		Collision detectCollision(
			const Collider* mainCollider,
			const Collider* otherCollider
		) const;
	};
}

