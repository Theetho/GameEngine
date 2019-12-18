#pragma once

#include <vector>
#include "Collider.h"

class PhysicsEngine
{
public:
	static struct Collision
	{
		bool mCollide = false;
		float mDistance = 0.0f;
		sf::Vector2f mNormal = sf::Vector2f(0.0f, 0.0f);

		Collision(bool collide, float distance, sf::Vector2f normal)
			: mCollide(collide)
			, mDistance(distance)
			, mNormal(normal) {}
	};

	static PhysicsEngine* GetInstance();
	static void AddCollider(Collider* collider);
	static void RemoveCollider(Collider* collider);

	void OnUpdate(const double& delta);
private:
	PhysicsEngine();
	~PhysicsEngine();

	void ApplyGravity(std::vector<Collider*>& colliders);
	void ResolveCollision(std::vector<Collider*>& colliders);
	Collision DetectCollision(Collider* first, Collider* second);
	static PhysicsEngine* sInstance;

	const float GRAVITATIONAL_ACCELERATION = 9.81f;
	std::vector<Collider*> mColliders;
};

