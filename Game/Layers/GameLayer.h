#pragma once

class GameLayer : public Engine::Layer
{
public:
	GameLayer();
	~GameLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(const double& delta) override;
	void OnEvent(Engine::Event& event) override;
	void OnEngineGui() override;
private:
	void OnGui() override;

	Engine::Scene mScene;
	Engine::Color mClearColor;
	Engine::Camera3D mCamera;
	Engine::Cube mCube;
	Engine::Ref<Engine::FrameBuffer> mFrameBuffer;
};

