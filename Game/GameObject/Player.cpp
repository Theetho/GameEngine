#include "pch.h"
#include "Player.h"

Player::Player()
	: DynamicObject()
{
	m_components.push_back(new Engine::PhysicsComponent(this));
	m_components.push_back(new Engine::MovementComponent(this));
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
