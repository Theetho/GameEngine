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
	std::vector<std::shared_ptr<Engine::GameObject<2>>> mObjects;
	Engine::Camera2D mCamera;
	Engine::Renderer2D mRenderer;
};

