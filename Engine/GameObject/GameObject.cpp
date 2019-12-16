#include "EnginePch.h"
#include "GameObject.h"
#include "Include/Component.h"
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

	// Meant to be overrided
	void GameObject::onCollision(
		const Collision& collision
	)
	{
	}
	
	bool GameObject::isJumping() const
	{
		return false;
	}

	bool GameObject::isMoving() const
	{
		return false;
	}

	bool GameObject::isMoveable() const
	{
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