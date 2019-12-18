#include "pch.h"
#include "MapLayer.h"
#include "Util/FileLoader.h"

MapLayer::MapLayer()
	: m_player(Engine::AssetManager::getModelLibrary().load("nanosuit/nanosuit.obj", "player"))
	, m_camera(m_player)
	, m_skybox(std::make_shared<Engine::Skybox>("Skyboxes/Day", "skybox"))
{
}

MapLayer::~MapLayer()
{
}

void MapLayer::onAttach()
{
	/*   AXIS   y
				|   z
				|  /
				| /
		x_______|/

	*/

	m_maze = FileLoader::loadMap("Assets/MapFiles/maze.map");
	
	m_player.setPosition(m_maze->getEntry());
	m_player.setScale(0.05f);
	
	// Shader
	auto& shader		 = Engine::AssetManager::getShaderLibrary().load("lights_materials.glsl", "scene");
	auto& shaderPBR		 = Engine::AssetManager::getShaderLibrary().load("lights_PBR.glsl", "player");
	auto& shaderSkybox	 = Engine::AssetManager::getShaderLibrary().load("skybox.glsl");
	Engine::AssetManager::getShaderLibrary().load("colliders.glsl", "collider");


	Engine::AssetManager::getTexture2DLibrary().load("snow.jpg");
	Engine::AssetManager::getTexture2DLibrary().load("hedge.jpg");
	Engine::AssetManager::getTexture2DLibrary().load("floor.jpg");

	// Lights
	m_lights.push_back(std::make_shared<Engine::DirectionalLight>(Engine::Vec3(0.7f, -1.0f, .0f)));
	
	for (unsigned int i = 0; i < m_lights.size(); ++i)
	{
		m_lights[i]->load(shader, i);
		m_lights[i]->load(shaderPBR, i);
	}

	// Skybox
	m_skybox->load(shaderSkybox);

	/// For clear color : https://www.toutes-les-couleurs.com/code-couleur-rvb.php
	Engine::RenderCommand::setClearColor(Engine::Color::Aqua);
	Engine::Input::toggleCursor();
}

void MapLayer::onDetach()
{
}

void MapLayer::onUpdate(const double& delta)
{
	m_player.onUpdate(delta);

	m_camera.onUpdate(delta);

	// Textures
	auto& snow  = Engine::AssetManager::getTexture2DLibrary().get("snow");
	auto& floor = Engine::AssetManager::getTexture2DLibrary().get("floor");
	auto& wall  = Engine::AssetManager::getTexture2DLibrary().get("hedge");

	// Shader
	auto shader			  = Engine::AssetManager::getShaderLibrary().get("scene");
	auto shaderPBR	      = Engine::AssetManager::getShaderLibrary().get("player");
	auto shader_collider  = Engine::AssetManager::getShaderLibrary().get("collider");
	auto shaderSkybox	  = Engine::AssetManager::getShaderLibrary().load("skybox");
	auto openglShader     = std::dynamic_pointer_cast<Engine::OpenGLShader>(shader);
	auto openglShaderPBR  = std::dynamic_pointer_cast<Engine::OpenGLShader>(shaderPBR);

	// Model
		// Loaded in player.cpp
	auto player = Engine::AssetManager::getModelLibrary().get("player");
		// Loaded in Map.cpp
	auto cube   = Engine::AssetManager::getModelLibrary().get("cube");
	
	// Materials
	Engine::Ref<Engine::Material> material;
	
	// --- Rendering ---
	
	Engine::RenderCommand::clear();

	Engine::Renderer::BeginScene(m_camera, shader);

	// Draw Walls
	material = std::make_shared<Engine::RawMaterial>(Engine::RawMaterial::Emerald);
	cube->setMaterial(material);

	for (auto& wall : m_maze->getWalls())
	{
		Engine::Renderer::Submit(*wall.getModel(), wall.getTransform());
	}

	// Draw Floor
	for (auto& floor : m_maze->getFloor())
	{
		Engine::Renderer::Submit(*floor.getModel() , floor.getTransform());
	}
	
	Engine::Renderer::EndScene();

	// -----------------
	
	Engine::Renderer::BeginScene(m_camera, shaderPBR);
	
	// Draw Player
	Engine::Renderer::Submit(*player, m_player.getTransform());

	Engine::Renderer::EndScene();
	
	// -----------------

	Engine::Renderer::BeginScene(m_camera, shader_collider);
	
	Engine::Renderer::Submit(*cube, m_player.GetComponent<Engine::BoxCollider>());

	Engine::Renderer::EndScene();

	// -----------------

	// Skybox
	Engine::Renderer::BeginScene(m_camera, shaderSkybox);

	Engine::Renderer::Submit(*m_skybox);

	Engine::Renderer::EndScene();

	// -----------------
}

void MapLayer::onEvent(Engine::Event& event)
{
	m_camera.onEvent(event);
	m_player.onEvent(event);
}
