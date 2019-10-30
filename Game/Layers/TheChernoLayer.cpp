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
	auto& shader = Engine::AssetManager::getShaderLibrary().load("texture.glsl");

	m_cubes.push_back(Cube(1.0f, Engine::Transform(Engine::Vec3(-2, 0, -2))));
	m_cubes.push_back(Cube(1.0f, Engine::Transform(Engine::Vec3(-2, 0,  0))));
	m_cubes.push_back(Cube(1.0f, Engine::Transform(Engine::Vec3(-2, 0,  2))));
	m_cubes.push_back(Cube(1.0f, Engine::Transform(Engine::Vec3( 0, 0, -2))));
	m_cubes.push_back(Cube(1.0f, Engine::Transform(Engine::Vec3( 0, 0,  0))));
	m_cubes.push_back(Cube(1.0f, Engine::Transform(Engine::Vec3( 0, 0,  2))));
	m_cubes.push_back(Cube(1.0f, Engine::Transform(Engine::Vec3( 2, 0, -2))));
	m_cubes.push_back(Cube(1.0f, Engine::Transform(Engine::Vec3( 2, 0,  0))));
	m_cubes.push_back(Cube(1.0f, Engine::Transform(Engine::Vec3( 2, 0,  2))));
	
	Engine::AssetManager::getTexture2DLibrary().load("ground.jpg");

	shader->bind();
	std::dynamic_pointer_cast<Engine::OpenGLShader>(shader)->uploadUniform(
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

	auto& texture = Engine::AssetManager::getTexture2DLibrary().get("ground");
	auto& shader  = Engine::AssetManager::getShaderLibrary().get("texture");

	texture->bind(0);
	for (auto& cube : m_cubes)
	{
		Engine::Renderer::submit(
			shader,
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
