#pragma once

#include "Bomb.h"

class Player : public Engine::GameObject
{
public:
	Player(Engine::Ref<Engine::Model> model, const Engine::Transform& transform = Engine::Transform());
	~Player();

	void OnUpdate(const double& delta) override;
	void OnEvent(Engine::Event& event) override;
	void OnCollision(const Engine::Collision& collision) override;

	const Engine::Ref<Engine::Model> GetModel() const;
	std::vector<Engine::Ref<Bomb>>& GetBombs();
	bool IsMoveable() const override;

	void SetModel(Engine::Ref<Engine::Model> model);
private:
	Engine::Ref<Engine::Model>	   mModel;
	std::vector<Engine::Ref<Bomb>> mBombs;
	float mBombPower = 1.5f;

	void Render(Engine::Ref<Engine::RenderCommand> render_command, Engine::Ref<Engine::Shader> shader) const override;
};


