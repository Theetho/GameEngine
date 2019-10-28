#pragma once

#include "Engine/Core/Layer.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/VertexArray.h"

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
	std::shared_ptr<Engine::Shader>		  m_shader;
	std::shared_ptr<Engine::VertexArray>  m_vao;
	std::shared_ptr<Engine::VertexArray>  m_squareVao;
	Engine::Camera3D					  m_camera;
};
