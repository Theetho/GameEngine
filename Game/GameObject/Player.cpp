#include "pch.h"
#include "Player.h"

using namespace Engine;

Player::Player(
	Ref<Model> model,
	const Transform& transform
)
	: GameObject(transform)
{
	AddComponent<PhysicsComponent>(std::make_shared<PhysicsComponent>(*this));

	AddComponent<MovementComponent>(std::make_shared<MovementComponent>(*this));

	this->setModel(model);
}

Player::~Player()
{
}

void Player::onEvent(Engine::Event& event)
{
	if (event.type == Engine::Event::KeyPressed && event.keyEvent.code == ENGINE_KEY_SPACE)
	{
		Ref<Bomb> bomb = std::make_shared<Bomb>(
			AssetManager::getModelLibrary().get("bomb"),
			m_transform
		);
	
		// Translate the bomb so the bottom is just on the floor
		float floorLevel = m_transform.getPosition().y - (m_model->getSize().y * m_transform.getScale().y / 2.0f);

		bomb->setPosition({
			bomb->getTransform().getPosition().x,
			floorLevel + (bomb->getModel().getSize().y * bomb->getTransform().getScale().y / 2.0f),
			bomb->getTransform().getPosition().z
		});


		m_bombs.push_back(std::move(bomb));
		/*auto physics = GetComponent<PhysicsComponent>();

		if (physics && !physics->isInAir())
			physics->jump();*/
	}
}

void Player::setModel(
	Engine::Ref<Engine::Model> model
)
{
	m_model = model;

	m_model->setMaterial(
		std::make_shared<RawMaterial>(RawMaterial::Emerald)
	);

	Vec3 size = model->getSize();

	AddComponent<BoxCollider>(
		std::make_shared<BoxCollider>(
			*this,
			m_transform.getPosition(),
			size.x, size.y, size.z
		)
	);
}
