#include "pch.h"
#include "TheChernoLayer.h"

TheChernoLayer::TheChernoLayer()
	: m_camera(Engine::Vec3(0, 1, 5))
	, m_cubes()
{
}

TheChernoLayer::~TheChernoLayer()
{
}

void TheChernoLayer::onAttach()
{
	// Shader
	m_shader = Engine::Shader::create("cubeV.glsl");

	m_cubes.push_back(Cube(1.0f, Engine::Transform(Engine::Vec3(-2, 0, -2))));
	m_cubes.push_back(Cube(1.0f, Engine::Transform(Engine::Vec3(-2, 0,  0))));
	m_cubes.push_back(Cube(1.0f, Engine::Transform(Engine::Vec3(-2, 0,  2))));
	m_cubes.push_back(Cube(1.0f, Engine::Transform(Engine::Vec3( 0, 0, -2))));
	m_cubes.push_back(Cube(1.0f, Engine::Transform(Engine::Vec3( 0, 0,  0))));
	m_cubes.push_back(Cube(1.0f, Engine::Transform(Engine::Vec3( 0, 0,  2))));
	m_cubes.push_back(Cube(1.0f, Engine::Transform(Engine::Vec3( 2, 0, -2))));
	m_cubes.push_back(Cube(1.0f, Engine::Transform(Engine::Vec3( 2, 0,  0))));
	m_cubes.push_back(Cube(1.0f, Engine::Transform(Engine::Vec3( 2, 0,  2))));
	
	m_texture = Engine::Texture2D::create("ground.jpg");

	m_shader->bind();
	std::dynamic_pointer_cast<Engine::OpenGLShader>(m_shader)->uploadUniform(
		"u_texture",
		0
	);

	/// For clear color : https://www.toutes-les-couleurs.com/code-couleur-rvb.php
	Engine::RenderCommand::setClearColor(Engine::Color(254, 254, 224));
	Engine::Input::toggleCursor();
}

void TheChernoLayer::onDetach()
{
}

void TheChernoLayer::onUpdate(const double& delta)
{
	m_camera.onUpdate(delta);

	// --- Rendering ---
	Engine::RenderCommand::clear();

	Engine::Renderer::beginScene(m_camera);

	m_texture->bind(0);
	for (auto& cube : m_cubes)
	{
		Engine::Renderer::submit(
			m_shader, 
			cube.getVao(),
			cube.getTransform()
		);
	}

	Engine::Renderer::endScene();
	// -----------------
}

void TheChernoLayer::onEvent(Engine::Event& event)
{
	m_camera.onEvent(event);
}
