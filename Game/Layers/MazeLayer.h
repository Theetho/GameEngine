#pragma once

#include "Models/Maze.h"

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
	Engine::Camera3D    m_camera;
	Engine::Character   m_character;
	Engine::Scope<Maze> m_maze;
};

