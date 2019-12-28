#pragma once

#include "GameObject/Player.h"
#include "Map/Map.h"
#include "GameObject/Bomb.h"
#include "Core/Camera.h"

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
	Camera									mCamera;
	Player									mPlayer;
	Engine::Scope<Map>						mMap;
	std::vector<Engine::Ref<Engine::Light>> mLights;
	std::vector<Engine::Ref<Bomb>>			mBombs;
	Engine::Skybox							mSkybox;
};

