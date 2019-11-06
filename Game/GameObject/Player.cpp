#include "pch.h"
#include "Player.h"

Player::Player()
	: DynamicObject()
{
	m_components.push_back(new Engine::PhysicsComponent(this));
	m_components.push_back(new Engine::MovementComponent(this));

	auto collider = new Engine::BoxCollider(this, Engine::Vec3(), 1.0f, 1.0f, 1.0f);
	//m_components.push_back(collider);

	Engine::CollisionSystem::addCollider(collider);
}

Player::~Player()
{
}

void Player::onUpdate(
	const double& delta
)
{
	GameObject::onUpdate(delta);
	m_direction = getComponent<Engine::MovementComponent>()->getDirection();
}

void Player::onEvent(Engine::Event& event)
{
	if (event.type == Engine::Event::KeyPressed && event.keyEvent.code == ENGINE_KEY_SPACE)
	{
		getComponent<Engine::PhysicsComponent>()->jump();
	}
}
