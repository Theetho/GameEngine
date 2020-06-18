#pragma once

class BombermanLayer : public Engine::Layer
{
public:
	BombermanLayer();
	~BombermanLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Engine::Ref<Engine::Camera3D> camera, const double& delta) override;
	void OnEvent(Engine::Event& event) override;
private:
	void OnGui() override;

	Engine::Terrain							mTerrain;
	Engine::Water							mLake;
	Engine::Skybox							mSkybox;
	Engine::Color mClearColor;

	bool mShowSkybox = true;
	bool mShowSky = false;
	// Hérité via Layer
	void OnEngineGui() override;
};

