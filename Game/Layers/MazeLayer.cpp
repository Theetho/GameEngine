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

	m_maze = FileLoader::loadMaze("Assets/MazeFiles/platform.mz");

	m_player.setPosition(m_maze->getEntry());
	m_player.setScale(0.05f);
	
	// Shader
	auto& shader		 = Engine::AssetManager::getShaderLibrary().load("lights_materials.glsl", "scene");
	auto& shaderPBR		 = Engine::AssetManager::getShaderLibrary().load("lights_PBR.glsl", "player");
	auto& shaderCollider = Engine::AssetManager::getShaderLibrary().load("colliders.glsl", "collider");

	Engine::AssetManager::getTexture2DLibrary().load("snow.jpg");
	Engine::AssetManager::getTexture2DLibrary().load("hedge.jpg");
	Engine::AssetManager::getTexture2DLibrary().load("floor.jpg");

	// Lights
	m_lights.push_back(std::make_shared<Engine::PointLight>(Engine::Vec3(-5.0f, 3.0f, -5.0f), Engine::PointLight::Attenuation(/*1.8f, 0.7*/), Engine::Color(1.0f)));
	m_lights.push_back(std::make_shared<Engine::PointLight>(Engine::Vec3(-5.0f, 3.0f,  5.0f), Engine::PointLight::Attenuation(/*1.8f, 0.7*/), Engine::Color(0.2f)));
	m_lights.push_back(std::make_shared<Engine::PointLight>(Engine::Vec3( 5.0f, 3.0f, -5.0f), Engine::PointLight::Attenuation(/*1.8f, 0.7*/), Engine::Color(0.2f)));
	m_lights.push_back(std::make_shared<Engine::PointLight>(Engine::Vec3( 5.0f, 3.0f,  5.0f), Engine::PointLight::Attenuation(/*1.8f, 0.7*/), Engine::Color(0.2f)));
	
	for (unsigned int i = 0; i < m_lights.size(); ++i)
	{
		m_lights[i]->load(shader, i);
		m_lights[i]->load(shaderPBR, i);
	}

	/// For clear color : https://www.toutes-les-couleurs.com/code-couleur-rvb.php
	Engine::RenderCommand::setClearColor(Engine::Color::Aqua);
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
	auto& openglShader    = std::dynamic_pointer_cast<Engine::OpenGLShader>(shader);
	auto& openglShaderPBR = std::dynamic_pointer_cast<Engine::OpenGLShader>(shaderPBR);

	// Model
		// Loaded in player.cpp
	auto player = Engine::AssetManager::getModelLibrary().get("player");
		// Loaded in Maze.cpp
	auto cube   = Engine::AssetManager::getModelLibrary().get("cube");
	
	// Materials
	Engine::Ref<Engine::Material> material;
	
	Engine::Renderer::BeginScene(m_camera, shader);

	/* Draw Walls */
	material = std::make_shared<Engine::RawMaterial>(Engine::RawMaterial::Emerald);
	cube->setMaterial(material);

	for (auto& wall : m_maze->getWalls())
	{
		Engine::Renderer::Submit(cube, wall->getTransform());
	}

	/* Draw Floor */
	material = std::make_shared<Engine::RawMaterial>(Engine::RawMaterial::Obsidian);
	cube->setMaterial(material);

	for (auto& floor : m_maze->getFloor())
	{
		Engine::Renderer::Submit(cube, floor->getTransform());
	}
	
	Engine::Renderer::EndScene();

	// -----------------
	
	Engine::Renderer::BeginScene(m_camera, shaderPBR);
	
	/* Draw Player */
	Engine::Renderer::Submit(player, m_player.getTransform());

	Engine::Renderer::EndScene();

	// -----------------
}

void MazeLayer::onEvent(Engine::Event& event)
{
	m_camera.onEvent(event);
	m_player.onEvent(event);
}
