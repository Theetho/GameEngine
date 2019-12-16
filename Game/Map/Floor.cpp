#include "pch.h"
#include "Floor.h"

using namespace Engine;

Ref<Model> Floor::s_model;
bool Floor::s_isInitialized = false;

Floor::Floor(
	const Transform& transform
)
	: GameObject(transform)
{
	if (!s_isInitialized)
	{
		s_isInitialized = true;

		s_model = AssetManager::getModelLibrary().load("cube/cube.obj", "floor");

		auto texture = std::vector<Ref<Texture2D>>({ AssetManager::getTexture2DLibrary().load("lawn.png")});

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

Floor::~Floor()
{
}
