#pragma once

#include "Models/Map.h"
#include "GameObject/Player.h"

class MapLayer : public Engine::Layer
{
public:
	MapLayer();
	~MapLayer();

	virtual void onAttach() override;

	virtual void onDetach() override;

	virtual void onUpdate(const double& delta) override;

	virtual void onEvent(Engine::Event& event) override;
private:
	Engine::Camera3DLocked					m_camera;
	Engine::Scope<Map>						m_maze;
	Player									m_player;
	std::vector<Engine::Ref<Engine::Light>> m_lights;
	Engine::Ref<Engine::Skybox>			    m_skybox;
};

