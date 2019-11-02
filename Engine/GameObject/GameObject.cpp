#include "EnginePch.h"
#include "GameObject.h"
#include "Component.h"

namespace Engine
{
	GameObject::GameObject(
		const Transform& transform,
		Material* material,
		Texture* texture
	)
		: m_transform(transform)
		, m_material(material)
		, m_texture(texture)
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
}