#include "pch.h"
#include "Wall.h"

using namespace Engine;

Ref<Model> Wall::s_model;
bool Wall::s_isInitialized = false;

Wall::Wall(
	const Transform& transform
)
	: GameObject(transform)
{
	if (!s_isInitialized)
	{
		s_isInitialized = true;

		s_model = AssetManager::getModelLibrary().load("cube/cube.obj", "wall");

		auto texture = std::vector<Ref<Texture2D>>({ AssetManager::getTexture2DLibrary().load("wall.jpg", "wall") });

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

Wall::~Wall()
{
}
