#include "pch.h"
#include "BombermanLayer.h"
#include "Util/FileLoader.h"

using namespace Engine;

BombermanLayer::BombermanLayer()
	: m_player(AssetManager::getModelLibrary().load("cube/cube.obj", "player"))
	, m_camera(m_player)
{
}

BombermanLayer::~BombermanLayer()
{}

void BombermanLayer::onAttach()
{
	m_map = FileLoader::loadMap("Assets/MapFiles/map_1.map");

	AssetManager::getModelLibrary().load("sphere/sphere.obj", "bomb");

	m_player.setPosition(m_map->getEntry());
	m_player.setScale(0.3f);

	m_lights.push_back(
		std::make_shared<DirectionalLight>(Vec3(0.0f, -1.0f, 0.0f))
	);
	
	Ref<Shader> shader = AssetManager::getShaderLibrary().load("lights_materials.glsl", "scene");

	for (int i = 0; i < m_lights.size(); ++i)
	{
		m_lights[i]->load(shader, i);
	}

	RenderCommand::setClearColor(Color::Black);
	Input::toggleCursor();
}

void BombermanLayer::onDetach()
{}

void BombermanLayer::onUpdate(const double& delta)
{
	m_player.onUpdate(delta);
	m_camera.onUpdate(delta);

	for (Ref<Bomb> bomb : m_player.getBombs())
	{
		m_bombs.push_back(std::move(bomb));
	}
	
	RenderCommand::clear();

	Ref<Shader> shader = AssetManager::getShaderLibrary().get("scene");

	Renderer::BeginScene(m_camera, shader);

	for (auto wall : m_map->getWalls())
		Renderer::Submit(*wall.getModel(), wall.getTransform());

	for (auto floor : m_map->getFloor())
		Renderer::Submit(*floor.getModel(), floor.getTransform());

	Renderer::Submit(*m_player.getModel(), m_player.getTransform());

	auto bomb = m_bombs.begin();
	for (unsigned int i = 0; i < m_bombs.size(); ++i, ++bomb)
	{
		if (m_bombs[i]->hasExploded)
		{
			m_bombs.erase(bomb);
			continue;
		}
		
		m_bombs[i]->onUpdate(delta);
		Renderer::Submit(m_bombs[i]->getModel(), m_bombs[i]->getTransform());
	}

	Renderer::EndScene();
}

void BombermanLayer::onEvent(Engine::Event & event)
{
	m_camera.onEvent(event);
	m_player.onEvent(event);
}
