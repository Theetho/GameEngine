#pragma once

#include "Bomb.h"

class Player : public Engine::GameObject
{
public:
	Player(
		Engine::Ref<Engine::Model> model,
		const Engine::Transform& transform = Engine::Transform()
	);
	~Player();

	void onEvent(
		Engine::Event& event
	) override;

	inline const Engine::Ref<Engine::Model> getModel() const
	{
		return m_model;
	}

	void setModel(
		Engine::Ref<Engine::Model> model
	);

	inline std::vector<Engine::Ref<Bomb>>& getBombs()
	{
		return m_bombs;
	}

private:
	Engine::Ref<Engine::Model>	   m_model;
	std::vector<Engine::Ref<Bomb>> m_bombs;
};


