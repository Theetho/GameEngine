#include "pch.h"
#include "MazeLayer.h"
#include "Util/FileLoader.h"

MazeLayer::MazeLayer()
	: m_camera(Engine::Vec3(0, 1, 5))
{
}

MazeLayer::~MazeLayer()
{
}

void MazeLayer::onAttach()
{
	// Shader
	auto& shader = Engine::AssetManager::getShaderLibrary().load("color.glsl");

	m_maze = FileLoader::loadMaze("Assets/MazeFiles/maze.mz");

	Cube cube;

	m_player.setVao(cube.getVao());

	m_player.setPosition(m_maze->getEntry());
	m_player.getCameraController().setOffset(Engine::Vec3(0.0f, 5.0f, 3.0f));
	m_camera.getControlled(&m_player.getCameraController());

	Engine::AssetManager::getTexture2DLibrary().load("snow.jpg");
	Engine::AssetManager::getTexture2DLibrary().load("hedge.jpg");
	Engine::AssetManager::getTexture2DLibrary().load("ground.jpg");

	/// For clear color : https://www.toutes-les-couleurs.com/code-couleur-rvb.php
	Engine::RenderCommand::setClearColor(Engine::Color::Black);
	Engine::Input::toggleCursor();
}

void MazeLayer::onDetach()
{
}

void MazeLayer::onUpdate(const double& delta)
{
	m_player.onUpdate(delta);

	m_camera.onUpdate(delta);

	// --- Rendering ---
	Engine::RenderCommand::clear();

	Engine::Renderer::beginScene(m_camera);

	auto& snow = Engine::AssetManager::getTexture2DLibrary().get("snow");
	auto& ground = Engine::AssetManager::getTexture2DLibrary().get("ground");
	auto& wall = Engine::AssetManager::getTexture2DLibrary().get("hedge");
	auto& shader  = Engine::AssetManager::getShaderLibrary().get("color");

	//wall->bind();
	shader->bind();
	std::dynamic_pointer_cast<Engine::OpenGLShader>(shader)->uploadUniform(
		"u_color",
		Engine::Color::Navy
	);
	for (auto& cube : m_maze->getWalls())
	{
		Engine::Renderer::submit(
			shader,
			cube.getVao(),
			cube.getTransform()
		);
	}

	//snow->bind();
	std::dynamic_pointer_cast<Engine::OpenGLShader>(shader)->uploadUniform(
		"u_color",
		Engine::Color::Teal
	);
	for (auto& cube : m_maze->getGround())
	{
		Engine::Renderer::submit(
			shader,
			cube.getVao(),
			cube.getTransform()
		);
	}

	//ground->bind();
	std::dynamic_pointer_cast<Engine::OpenGLShader>(shader)->uploadUniform(
		"u_color",
		Engine::Color::Yellow
	);
	Engine::Renderer::submit(
		shader,
		m_player.getVao(),
		m_player.getTransform()
	);

	Engine::Renderer::endScene();
	// -----------------
}

void MazeLayer::onEvent(Engine::Event& event)
{
	m_camera.onEvent(event);
	m_player.onEvent(event);
}
