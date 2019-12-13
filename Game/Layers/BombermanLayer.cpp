#include "pch.h"
#include "BombermanLayer.h"
#include "Util/FileLoader.h"

using namespace Engine;

BombermanLayer::BombermanLayer()
	: m_camera(m_player)
{
}

BombermanLayer::~BombermanLayer()
{}

void BombermanLayer::onAttach()
{
	m_map = FileLoader::loadMap("Assets/MapFiles/map_1.map");

	Ref<Shader> shader = AssetManager::getShaderLibrary().load("lights_materials.glsl", "scene");
	AssetManager::getShaderLibrary().load("colliders.glsl", "collider");
	Ref<Model> cube = AssetManager::getModelLibrary().load("cube/cube.obj", "cube");


	m_player.setPosition(m_map->getEntry());
	m_player.setModel(cube);
	m_player.setScale(0.2);

	m_lights.push_back(
		std::make_shared<SpotLight>(Vec3(0.0f, 7.0f, 0.0f), Vec3(0.0f, -1.0f, 0.0f), 50.0f)
	);

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
	
	RenderCommand::clear();

	Ref<Shader> shader = AssetManager::getShaderLibrary().get("scene");
	Ref<Shader> shader_collider = AssetManager::getShaderLibrary().get("collider");
	Ref<Model> cube = AssetManager::getModelLibrary().get("cube");
	Ref<RawMaterial> material;

	Renderer::BeginScene(m_camera, shader);

	material = std::make_shared<RawMaterial>(RawMaterial::Emerald);
	cube->setMaterial(material);
	for (auto wall : m_map->getWalls())
		Renderer::Submit(cube, wall->getTransform());

	material = std::make_shared<RawMaterial>(RawMaterial::Bronze);
	cube->setMaterial(material);
	for (auto floor : m_map->getFloor())
		Renderer::Submit(cube, floor->getTransform());

	material = std::make_shared<RawMaterial>(RawMaterial::Brass);
	cube->setMaterial(material);
	Renderer::Submit(m_player.getModel(), m_player.getTransform());

	Renderer::EndScene();
}

void BombermanLayer::onEvent(Engine::Event & event)
{
	m_camera.onEvent(event);
	m_player.onEvent(event);
}
