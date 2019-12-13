#pragma once

#include "GameObject/Player.h"
#include "Models/Map.h"

class BombermanLayer : public Engine::Layer
{
public:
	BombermanLayer();
	~BombermanLayer();

	void onAttach() override;
	void onDetach() override;
	void onUpdate(const double& delta) override;
	void onEvent(Engine::Event& event) override;

private:
	Engine::Camera3DLocked					m_camera;
	Player									m_player;
	Engine::Scope<Map>						m_map;
	std::vector<Engine::Ref<Engine::Light>> m_lights;
};
