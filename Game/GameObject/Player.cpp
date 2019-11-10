#include "pch.h"
#include "Player.h"

Player::Player(
	const Engine::Transform& transform
)
	: GameObject(transform)
{
	AddComponent<Engine::PhysicsComponent>(std::make_shared<Engine::PhysicsComponent>(
		*this
		)
	);

	AddComponent<Engine::MovementComponent>(std::make_shared<Engine::MovementComponent>(
		*this
		)
	);

	AddComponent<Engine::BoxCollider>(std::make_shared<Engine::BoxCollider>(
			*this,
			m_transform.getPosition(),
			1.0f, 1.0f, 1.0f
		)
	);
}

Player::~Player()
{
}

void Player::onEvent(Engine::Event& event)
{
	if (event.type == Engine::Event::KeyPressed && event.keyEvent.code == ENGINE_KEY_SPACE)
	{
		auto physics = GetComponent<Engine::PhysicsComponent>();
		
		if (physics && !physics->isInAir())
		{
			physics->jump();
		}
	}
}
