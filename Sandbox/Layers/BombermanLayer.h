#pragma once

class BombermanLayer : public Engine::Layer
{
public:
	BombermanLayer();
	~BombermanLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(const double& delta) override;
	void OnEvent(Engine::Event& event) override;
private:
	void OnGui() override;

	Engine::Camera3D						mCamera;
	Engine::Terrain							mTerrain;
	Engine::Water							mLake;
	std::vector<Engine::Ref<Engine::Light>> mLights;
	Engine::Skybox							mSkybox;
	Engine::GUIElement						mGui;
	Engine::Font							mFont;
	Engine::Text							mText;
};

