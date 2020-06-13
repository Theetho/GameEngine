#pragma once

#include "Core/CameraFree.h"
#include "Terrain/Terrain.h"

class TerrainLayer : public Engine::Layer
{
public:
	TerrainLayer();
	~TerrainLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(const double& delta) override;
	void OnEvent(Engine::Event& event) override;
private:
	CameraFree								mCamera;
	std::vector<Engine::Ref<Engine::Light>> mLights;
	::Terrain								mTerrain;
	Engine::Skybox							mSkybox;
};

