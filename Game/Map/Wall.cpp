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

		s_model->setMaterial(
			std::make_shared<RawMaterial>(
				RawMaterial(
					Color(0.3f, 0.3f, 0.3f),
					Color(0.4f, 0.4f, 0.4f),
					Color(0.5f, 0.5f, 0.5f),
					32.f
				)
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
