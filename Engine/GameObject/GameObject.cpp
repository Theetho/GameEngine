#include "EnginePch.h"
#include "GameObject.h"
#include "Component.h"

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
		for (auto component : m_components)
		{
			component->onUpdate(delta);
		}
	}

	// Meant to be overrided
	void GameObject::onEvent(
		Event& event
	)
	{
	}
	
	bool GameObject::isJumping() const
	{
		auto variant = getComponent<Component::Type::Physics, PhysicsComponent>();
		
		if (auto component = std::get_if<Ref<PhysicsComponent>>(&variant))
		{
			return (*component)->isJumping();
		}
		
		return false;
	}

	bool GameObject::isMoving() const
	{
		auto variant = getComponent<Component::Type::Movement, MovementComponent>();
		
		if (auto component = std::get_if<Ref<MovementComponent>>(&variant))
		{
			return (*component)->isMoving();
		}
		
		return false;
	}

	void GameObject::setScale(const Vec3& scale)
	{
		m_transform.setScale(scale);

		// Update the collider scale if the object has one
		auto box = getComponent<Component::Type::BoxCollider, BoxCollider>();
		auto sphere = getComponent<Component::Type::SphereCollider, SphereCollider>();

		if (auto collider = std::get_if<Ref<BoxCollider>>(&box))
		{
			(*collider)->setScale(scale);
		}
		else if (auto collider = std::get_if<Ref<SphereCollider>>(&sphere))
		{
			(*collider)->setScale(scale.x);
		}
	}
}