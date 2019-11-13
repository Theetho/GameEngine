#pragma once

#include "Models/Maze.h"
#include "GameObject/Player.h"

class MazeLayer : public Engine::Layer
{
public:
	MazeLayer();
	~MazeLayer();

	virtual void onAttach() override;

	virtual void onDetach() override;

	virtual void onUpdate(const double& delta) override;

	virtual void onEvent(Engine::Event& event) override;
private:
	Engine::Camera3DLocked	 m_camera;
	Engine::Scope<Maze>		 m_maze;
	Player					 m_player;
	Engine::DirectionalLight m_light;
};

