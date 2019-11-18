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
	auto& shader		 = Engine::AssetManager::getShaderLibrary().load("lights_materials.glsl", "scene");
	auto& shaderPBR		 = Engine::AssetManager::getShaderLibrary().load("lights_materialsPBR.glsl", "player");
	auto& shaderCollider = Engine::AssetManager::getShaderLibrary().load("colliders.glsl", "collider");

	Engine::AssetManager::getTexture2DLibrary().load("snow.jpg");
	Engine::AssetManager::getTexture2DLibrary().load("hedge.jpg");
	Engine::AssetManager::getTexture2DLibrary().load("floor.jpg");

	// Lights
	m_lights.push_back(std::make_shared<Engine::DirectionalLight>(Engine::Vec3(-1.0f, -1.0f, 0.0f), Engine::Color(0.1f)));
	m_lights.push_back(std::make_shared<Engine::PointLight>(Engine::Vec3(-5.0f, 1.0f,  5.0f), Engine::PointLight::Attenuation(1.8f, 0.7)));//, Engine::Color::Red));
	//m_lights.push_back(std::make_shared<Engine::PointLight>(Engine::Vec3(-5.0f, 1.0f, -5.0f), Engine::PointLight::Attenuation(1.8f, 0.7)));//, Engine::Color::Green));
	//m_lights.push_back(std::make_shared<Engine::PointLight>(Engine::Vec3( 5.0f, 1.0f,  5.0f), Engine::PointLight::Attenuation(1.8f, 0.7)));//, Engine::Color::Blue));
	//m_lights.push_back(std::make_shared<Engine::PointLight>(Engine::Vec3( 5.0f, 1.0f, -5.0f), Engine::PointLight::Attenuation(1.8f, 0.7)));//, Engine::Color::Yellow));
	m_lights.push_back(std::make_shared<Engine::SpotLight>(Engine::Vec3(-1.0f, 2.0f, 0.0f), Engine::Vec3(0.0f, -1.0f, 0.0f), 50.0f));
	
	for (unsigned int i = 0; i < m_lights.size(); ++i)
	{
		m_lights[i]->load(shader, i);
		m_lights[i]->load(shaderPBR, i);
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

	// Textures
	auto& snow  = Engine::AssetManager::getTexture2DLibrary().get("snow");
	auto& floor = Engine::AssetManager::getTexture2DLibrary().get("floor");
	auto& wall  = Engine::AssetManager::getTexture2DLibrary().get("hedge");

	// Shader
	auto& shader	      = Engine::AssetManager::getShaderLibrary().get("scene");
	auto& shaderPBR	      = Engine::AssetManager::getShaderLibrary().get("player");
	auto& colliderShader  = Engine::AssetManager::getShaderLibrary().get("collider");
	auto& openglShader    = std::dynamic_pointer_cast<Engine::OpenGLShader>(shader);
	auto& openglShaderPBR = std::dynamic_pointer_cast<Engine::OpenGLShader>(shaderPBR);
	auto& openglCollider  = std::dynamic_pointer_cast<Engine::OpenGLShader>(colliderShader);

	// Model
		// Loaded in player.cpp
	auto player = Engine::AssetManager::getModelLibrary().get("player");
		// Loaded in Maze.cpp
	auto cube   = Engine::AssetManager::getModelLibrary().get("cube");
	
	// Materials
	Engine::RawMaterial material;
	
	Engine::Renderer::BeginScene(m_camera, shader);

	/* Draw Walls */
	
	material = Engine::RawMaterial::Emerald;
	material.load(openglShader);

	for (auto& wall : m_maze->getWalls())
	{
		Engine::Renderer::Submit(cube, wall->getTransform());
	}

	/* Draw Floor */

	material = Engine::RawMaterial::Obsidian;
	material.load(openglShader);

	for (auto& floor : m_maze->getFloor())
	{
		Engine::Renderer::Submit(cube, floor->getTransform());
	}
	
	Engine::Renderer::EndScene();

	// -----------------
	
	Engine::Renderer::BeginScene(m_camera, shaderPBR);
	
	/* Draw Player */
	
	//material = &Engine::RawMaterial::Gold;
	//material->load(openglShader);

	Engine::Renderer::Submit(player, m_player.getTransform());

	Engine::Renderer::EndScene();

	// -----------------

	Engine::Renderer::BeginScene(m_camera, colliderShader);
	
	auto& collider = m_player.GetComponent<Engine::BoxCollider>();
	
	/* Draw the player collider */
	Engine::Renderer::Submit(cube, collider);

	Engine::Renderer::EndScene();
	
	// -----------------
}

void MazeLayer::onEvent(Engine::Event& event)
{
	m_camera.onEvent(event);
	m_player.onEvent(event);
}
