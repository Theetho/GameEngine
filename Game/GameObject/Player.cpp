#include "pch.h"
#include "Player.h"

Player::Player(
	const Engine::Transform& transform
)
	: GameObject(transform)
{
	m_components.push_back(std::make_shared<Engine::PhysicsComponent>(
		*this
		)
	);

	m_components.push_back(std::make_shared<Engine::MovementComponent>(
		*this
		)
	);

	m_components.push_back(std::make_shared<Engine::BoxCollider>(
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
		auto variant = getComponent <Engine::Component::Type::Physics, Engine::PhysicsComponent >();

		if (auto physics = std::get_if<Engine::Ref<Engine::PhysicsComponent>>(&variant))
		{
			if (!isJumping())
			{
				(*physics)->jump();

			}
		}
	}
}
