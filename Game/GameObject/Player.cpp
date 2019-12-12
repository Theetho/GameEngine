#include "pch.h"
#include "Player.h"

using namespace Engine;

Player::Player(
	const Transform& transform
)
	: GameObject(transform)
{
	AddComponent<PhysicsComponent>(std::make_shared<PhysicsComponent>(*this));

	AddComponent<MovementComponent>(std::make_shared<MovementComponent>(*this));
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

void Player::setModel(
	Engine::Ref<Engine::Model> model)
{
	m_model = model;

	Vec3 size = model->getSize();

	AddComponent<BoxCollider>(
		std::make_shared<BoxCollider>(
			*this,
			m_transform.getPosition(),
			size.x, size.y, size.z
		)
	);
}
