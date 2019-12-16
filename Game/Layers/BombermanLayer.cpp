#include "pch.h"
#include "BombermanLayer.h"
#include "Util/FileLoader.h"

using namespace Engine;

BombermanLayer::BombermanLayer()
	: m_player(AssetManager::getModelLibrary().load("varyasuit/DolBarriersuit.obj", "player"))
	, m_camera(m_player, 6.0f)
	, m_skybox("Skyboxes/Day")
{
}

BombermanLayer::~BombermanLayer()
{}

void BombermanLayer::onAttach()
{
	m_map = FileLoader::loadMap("Assets/MapFiles/map_1.map");

	AssetManager::getModelLibrary().load("sphere/sphere.obj", "bomb");

	m_player.setPosition(m_map->getEntry());
	m_player.setScale(0.05f);

	m_lights.push_back(
		std::make_shared<DirectionalLight>(Vec3(0.05f, -1.0f, 0.0f), Color(0.7f, 0.7f, 0.7f))
	);
	
	Ref<Shader> shader = AssetManager::getShaderLibrary().load("lights_materials.glsl", "scene");
	Ref<Shader> shader_pbr = AssetManager::getShaderLibrary().load("lights_PBR.glsl", "player");
	AssetManager::getShaderLibrary().load("skybox.glsl", "skybox");

	for (int i = 0; i < m_lights.size(); ++i)
	{
		m_lights[i]->load(shader, i);
		m_lights[i]->load(shader_pbr, i);
	}

	RenderCommand::setClearColor(Color::Black);
	Input::toggleCursor();
}

void BombermanLayer::onDetach()
{}

void BombermanLayer::onUpdate(
	const double& delta
)
{
	m_player.onUpdate(delta);
	m_camera.onUpdate(delta);
	m_map->onUpdate(delta, m_bombs.size() == 0);

	while(m_player.getBombs().size())
	{
		auto bomb = m_player.getBombs()[m_player.getBombs().size() - 1];
		bomb->getSurroundingWalls(*m_map);
		m_bombs.push_back(bomb);
		m_player.getBombs().pop_back();
	}
	
	RenderCommand::clear();

	Ref<Shader> shader = AssetManager::getShaderLibrary().get("scene");
	Ref<Shader> shader_pbr = AssetManager::getShaderLibrary().get("player");
	Ref<Shader> shader_skybox = AssetManager::getShaderLibrary().get("skybox");

	Renderer::BeginScene(m_camera, shader_pbr);

	for (auto wall : m_map->getWalls())
		Renderer::Submit(*wall.getModel(), wall.getTransform());

	for (auto wall : m_map->getDestructibleWalls())
	{
		if (wall.isEnabled())
		{
			Renderer::Submit(*wall.getModel(), wall.getTransform());
		}
	}

	for (auto floor : m_map->getFloor())
		Renderer::Submit(*floor.getModel(), floor.getTransform());
	
	Renderer::Submit(*m_map->getExit().getModel(), m_map->getExit().getTransform());

	Renderer::Submit(*m_player.getModel(), m_player.getTransform());

	Renderer::EndScene();
	
	Renderer::BeginScene(m_camera, shader);
	
	auto bomb = m_bombs.begin();
	for (size_t i = 0; i < m_bombs.size();)
	{
		if (m_bombs[i]->hasExploded)
		{
			m_bombs.erase(bomb);
			continue;
		}
		
		m_bombs[i]->onUpdate(delta);
		Renderer::Submit(m_bombs[i]->getModel(), m_bombs[i]->getTransform());
		++i; ++bomb;
	}
	
	Renderer::EndScene();
	
	/*Renderer::BeginScene(m_camera, shader_skybox);
	
	Renderer::Submit(m_skybox);

	Renderer::EndScene();*/
}

void BombermanLayer::onEvent(
	Engine::Event & event
)
{
	m_camera.onEvent(event);
	m_player.onEvent(event);
}
