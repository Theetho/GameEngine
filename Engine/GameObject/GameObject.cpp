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

	GameObject::~GameObject()
	{
		for (auto component : m_components)
		{
			delete component;
		}
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
		auto component = getComponent<PhysicsComponent>();
		if (component)
		{
			return component->isJumping();
		}
		return false;
	}

	bool GameObject::isMoving() const
	{
		auto component = getComponent<MovementComponent>();
		if (component)
		{
			return component->isMoving();
		}
		return false;
	}

	DynamicObject::DynamicObject(
		const Transform& transform
	)
		: GameObject(transform)
		, m_direction(0.0f, 0.0f, 0.0f)
	{
	}
}