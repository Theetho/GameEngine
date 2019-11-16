#include "pch.h"
#include "MazeLayer.h"
#include "Util/FileLoader.h"

MazeLayer::MazeLayer()
	: m_camera(m_player)
{
}

MazeLayer::~MazeLayer()
{
}

void MazeLayer::onAttach()
{
	/*   AXIS   y
				|   z
				|  /
				| /
		x_______|/

	*/

	m_maze = FileLoader::loadMaze("Assets/MazeFiles/maze.mz");

	m_player.setPosition(m_maze->getEntry());
	m_player.setScale(0.05f);
	
	// Shader
	auto& shader = Engine::AssetManager::getShaderLibrary().load("Light/light.glsl");

	Engine::AssetManager::getTexture2DLibrary().load("snow.jpg");
	Engine::AssetManager::getTexture2DLibrary().load("hedge.jpg");
	Engine::AssetManager::getTexture2DLibrary().load("floor.jpg");

	// Lights
	m_lights.push_back(std::make_shared<Engine::DirectionalLight>(Engine::Vec3(-1.0f, -1.0f, 0.0f), Engine::Color(0.1f)));
	m_lights.push_back(std::make_shared<Engine::PointLight>(Engine::Vec3(5.0f, 1.0f, 5.0f), Engine::PointLight::Attenuation(1.8f, 0.7)));
	m_lights.push_back(std::make_shared<Engine::SpotLight>(Engine::Vec3(-1.0f, 2.0f, 0.0f), Engine::Vec3(0.0f, -1.0f, 0.0f), 50.0f));
	
	for (unsigned int i = 0; i < m_lights.size(); ++i)
	{
		m_lights[i]->load(shader, i);
	}

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

	Engine::Renderer::BeginScene(m_camera);

	// Textures
	auto& snow = Engine::AssetManager::getTexture2DLibrary().get("snow");
	auto& floor = Engine::AssetManager::getTexture2DLibrary().get("floor");
	auto& wall = Engine::AssetManager::getTexture2DLibrary().get("hedge");

	// Shader
	auto& shader  = Engine::AssetManager::getShaderLibrary().get("light");
	auto& openglShader = std::dynamic_pointer_cast<Engine::OpenGLShader>(shader);

	// Model
		// Loaded in player.cpp
	auto player = Engine::AssetManager::getModelLibrary().get("nanosuit");
		// Loaded in Maze.cpp
	auto cube = Engine::AssetManager::getModelLibrary().get("cube");
	
	Engine::Color* drawColor;

	openglShader->bind();
	openglShader->uploadUniform("u_cameraPosition", m_camera.getPosition());

	/* Draw Walls */
	
//	wall->bind();
	drawColor = &Engine::Color::DarkGreen;
	openglShader->uploadUniform("u_color", *drawColor);
	
	for (auto& wall : m_maze->getWalls())
	{
		Engine::Renderer::Submit(
			openglShader,
			cube,
			wall->getTransform()
		);
	}

	/* Draw Floor */
	
//	floor->bind();
	drawColor = &Engine::Color::Brown;
	openglShader->uploadUniform("u_color", *drawColor);
	
	for (auto& floor : m_maze->getFloor())
	{
		Engine::Renderer::Submit(
			openglShader,
			cube,
			floor->getTransform()
		);
	}

	/* Draw Player */
	
	//snow->bind();
	drawColor = m_player.isColliding() ? &Engine::Color::Red : &Engine::Color::Yellow;
	openglShader->uploadUniform("u_color", *drawColor);

	Engine::Renderer::Submit(
		openglShader,
		player,
		m_player.getTransform()
	);

	Engine::Renderer::EndScene();
	// -----------------
}

void MazeLayer::onEvent(Engine::Event& event)
{
	m_camera.onEvent(event);
	m_player.onEvent(event);
}
