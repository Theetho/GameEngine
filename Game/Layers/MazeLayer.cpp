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
	auto& shader = Engine::AssetManager::getShaderLibrary().load("texture.glsl");

	m_maze = FileLoader::loadMaze("Assets/MazeFiles/1st.mz");

	m_camera.setPosition(m_maze->getEntry());

	Engine::AssetManager::getTexture2DLibrary().load("snow.jpg");
	Engine::AssetManager::getTexture2DLibrary().load("hedge.jpg");

	shader->bind();
	std::dynamic_pointer_cast<Engine::OpenGLShader>(shader)->uploadUniform(
		"u_texture",
		0
	);

	/// For clear color : https://www.toutes-les-couleurs.com/code-couleur-rvb.php
	Engine::RenderCommand::setClearColor(Engine::Color::Black);
	Engine::Input::toggleCursor();
}

void MazeLayer::onDetach()
{
}

void MazeLayer::onUpdate(const double& delta)
{
	m_camera.onUpdate(delta);

	// --- Rendering ---
	Engine::RenderCommand::clear();

	Engine::Renderer::beginScene(m_camera);

	auto& ground = Engine::AssetManager::getTexture2DLibrary().get("snow");
	auto& wall = Engine::AssetManager::getTexture2DLibrary().get("hedge");
	auto& shader  = Engine::AssetManager::getShaderLibrary().get("texture");

	wall->bind(0);
	//shader->bind();
	//std::dynamic_pointer_cast<Engine::OpenGLShader>(shader)->uploadUniform(
	//	"u_color",
	//	Engine::Color::DarkGreen
	//);
	for (auto& cube : m_maze->getWalls())
	{
		Engine::Renderer::submit(
			shader,
			cube.getVao(),
			cube.getTransform()
		);
	}

	ground->bind(0);
	//std::dynamic_pointer_cast<Engine::OpenGLShader>(shader)->uploadUniform(
	//	"u_color",
	//	Engine::Color::Green
	//);
	for (auto& cube : m_maze->getGround())
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

void MazeLayer::onEvent(Engine::Event& event)
{
	m_camera.onEvent(event);
}
