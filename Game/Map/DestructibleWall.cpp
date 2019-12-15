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

	Vec3 size = s_model->getSize() * m_transform.getScale();

	this->AddComponent<BoxCollider>(
		std::make_shared<BoxCollider>(
			*this, m_transform.getPosition(), size.x, size.y, size.z
			)
		);
}

DestructibleWall::~DestructibleWall()
{
}

void DestructibleWall::explode()
{
	this->hasExploded = true;
}
