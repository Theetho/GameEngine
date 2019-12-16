#include "pch.h"
#include "DestructibleWall.h"

using namespace Engine;

Ref<Model> DestructibleWall::s_model;
bool DestructibleWall::s_isInitialized = false;

DestructibleWall::DestructibleWall(
	const Transform& transform
)
	: Wall(transform)
{
	if (!s_isInitialized)
	{
		s_isInitialized = true;

		s_model = AssetManager::getModelLibrary().load("cube/cube.obj", "destructible_wall");

		auto texture = std::vector<Ref<Texture2D>>({ AssetManager::getTexture2DLibrary().load("snow.jpg") });

		s_model->setMaterial(
			std::make_shared<PBRMaterial>(
				texture,
				texture,
				texture,
				texture
				)
		);
	}
}

DestructibleWall::~DestructibleWall()
{
}

void DestructibleWall::explode()
{
	this->hasExploded = true;
	// We hide the wall and destroy its collider
	// before removing it from the world
	this->disable();
}

void DestructibleWall::disable()
{
	RemoveComponent<Engine::BoxCollider>();
	m_enable = false;
}
