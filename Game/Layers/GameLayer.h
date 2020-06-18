#pragma once

class GameLayer : public Engine::Layer
{
public:
	GameLayer();
	~GameLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Engine::Ref<Engine::Camera3D> camera, const double& delta) override;
	void OnEvent(Engine::Event& event) override;
	void OnEngineGui() override;
private:
	void OnGui() override;

	Engine::Color mClearColor;
	Engine::Cube mCube;
};

