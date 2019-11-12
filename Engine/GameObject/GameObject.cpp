#include "EnginePch.h"
#include "GameObject.h"
#include "Component.h"
#include "Core/Log.h"

namespace Engine
{

	GameObject::GameObject(
		const Transform& transform
	)
		: m_transform(transform)
		, m_isColliding(false)
	{
	}

	GameObject::GameObject(
		const GameObject& other
	)
		: m_transform(other.m_transform)
		, m_isColliding(other.m_isColliding)
		, m_components(other.m_components)
	{
	}

	GameObject::GameObject(
		const GameObject&& other
	) noexcept
		: m_transform(other.m_transform)
		, m_isColliding(other.m_isColliding)
		, m_components(other.m_components)
	{
	}

	GameObject& GameObject::operator=(const GameObject& other)
	{
		m_transform = other.m_transform;
		m_isColliding = other.m_isColliding;
		m_components = other.m_components;

		return *this;
	}

	GameObject& GameObject::operator=(const GameObject&& other) noexcept
	{
		m_transform = other.m_transform;
		m_isColliding = other.m_isColliding;
		m_components = other.m_components;

		return *this;
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::onUpdate(
		const double& delta
	)
	{
		for (auto kv : m_components)
		{
			kv.second->onUpdate(delta);
		}
	}

	// Meant to be overrided
	void GameObject::onEvent(
		Event& event
	)
	{
	}

	void GameObject::onCollision(
		const Collision& collision
	)
	{
		const float epsilon = 0.05f;

		const auto& colliders = collision.getColliders();
		
		const Collider* myCollider = &collision.getColliders().first->getOwner() == this
									 ? colliders.first : colliders.second;
		const Collider* otherCollider = &collision.getColliders().first->getOwner() == this
									 ? colliders.second : colliders.first;
		
		// If they are close enough on the up axis, then
		// myCollider is on top of the other (collision
		// with the floor)
		if (collision.distanceUpAxis() < epsilon)
		{

			auto physics = GetComponent<PhysicsComponent>();

			if (physics)
				physics->setGroundLevel(otherCollider->getMax().y + myCollider->getCenter().y - myCollider->getMin().y);
		}
		// Else, it is a true collision
		else
			m_isColliding = true;
	}
	
	bool GameObject::isJumping() const
	{
		auto physics = GetComponent<PhysicsComponent>();
		
		if (physics)
			return physics->isJumping();
		return false;
	}

	bool GameObject::isMoving() const
	{
		auto movement = GetComponent<MovementComponent>();

		if (movement)
			return movement->isMoving();
		return false;
	}

	bool GameObject::isMoveable() const
	{
		auto movement = GetComponent<MovementComponent>();

		if (movement)
			return true;
		return false;
	}

	void GameObject::setScale(const Vec3& scale)
	{
		m_transform.setScale(scale);

		auto box    = GetComponent<BoxCollider>();
		auto sphere = GetComponent<SphereCollider>();
		
		if (box)
			box->setScale(scale);
		else if (sphere)
			sphere->setScale(scale.x);
	}
}