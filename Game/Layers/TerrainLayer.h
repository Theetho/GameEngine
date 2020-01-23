#pragma once

#include "Core/CameraFree.h"

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
	Engine::Skybox							mSkybox;
};

