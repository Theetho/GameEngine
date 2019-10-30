#pragma once

#include "Models/Cube.h"

class TheChernoLayer : public Engine::Layer
{
public:
	TheChernoLayer();
	~TheChernoLayer();

	virtual void onAttach() override;

	virtual void onDetach() override;

	virtual void onUpdate(const double& delta) override;

	virtual void onEvent(Engine::Event& event) override;
private:
	Engine::Camera3D				 m_camera;
	
	std::vector<Cube> m_cubes;
};

