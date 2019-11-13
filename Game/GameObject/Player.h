#pragma once

class Player : public Engine::GameObject
{
public:
	Player(
		const Engine::Transform& transform = Engine::Transform()
	);
	~Player();

	void onEvent(
		Engine::Event& event
	) override;
};


