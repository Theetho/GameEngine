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

	inline const Engine::Ref<Engine::Model> getModel() const
	{
		return m_model;
	}

	void setModel(
		Engine::Ref<Engine::Model> model
	);

private:
	Engine::Ref<Engine::Model> m_model;
};


