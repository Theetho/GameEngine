#pragma once

#include "Map/Map.h"
#include "GameObject/Player.h"

class MapLayer : public Engine::Layer
{
public:
	MapLayer();
	~MapLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(const double& delta) override;
	virtual void OnEvent(Engine::Event& event) override;
private:
	Engine::Camera3DLocked					mCamera;
	Engine::Scope<Map>						mMap;
	Player									mPlayer;
	std::vector<Engine::Ref<Engine::Light>> mLights;
	Engine::Ref<Engine::Skybox>			    mSkybox;
};

