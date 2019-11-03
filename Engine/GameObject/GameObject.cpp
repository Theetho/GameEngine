#include "EnginePch.h"
#include "GameObject.h"
#include "Component.h"

namespace Engine
{
	GameObject::GameObject(
		const Transform& transform
	)
		: m_transform(transform)
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
		return getComponent<PhysicsComponent>()->isJumping();
	}

	bool GameObject::isMoving() const
	{
		return getComponent<MovementComponent>()->isMoving();
	}

	DynamicObject::DynamicObject(
		const Transform& transform
	)
		: GameObject(transform)
		, m_direction(0.0f, 0.0f, 0.0f)
	{
	}
}