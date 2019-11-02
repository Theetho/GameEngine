#include "pch.h"
#include "Player.h"

Player::Player()
	: GameObject()
	, m_cameraController()
{
}

Player::~Player()
{
}

void Player::onUpdate(
	const double& delta
)
{
	GameObject::onUpdate(delta);
	m_cameraController.onUpdate(delta);
	m_transform.setPosition(m_cameraController.getTransform().getPosition());
}

void Player::onEvent(Engine::Event& event)
{
	m_cameraController.onEvent(event);
}
