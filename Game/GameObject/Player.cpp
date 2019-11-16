#include "pch.h"
#include "Player.h"

Player::Player(
	const Engine::Transform& transform
)
	: GameObject(transform)
{
	auto model = Engine::AssetManager::getModelLibrary().load("nanosuit/nanosuit.obj", "nanosuit");

	AddComponent<Engine::PhysicsComponent>(std::make_shared<Engine::PhysicsComponent>(
		*this
		)
	);

	AddComponent<Engine::MovementComponent>(std::make_shared<Engine::MovementComponent>(
		*this
		)
	);

	Engine::Vec3 size = model->getSize();
	AddComponent<Engine::BoxCollider>(
		std::make_shared<Engine::BoxCollider>(
			*this,
			//Engine::Vec3(size.x, size.y, size.z) / 2.0f,
			m_transform.getPosition(),
			size.x, size.y, size.z
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
