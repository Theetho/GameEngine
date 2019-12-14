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

		s_model->setMaterial(
			std::make_shared<RawMaterial>(
				RawMaterial(
					Color(167, 103, 38), // Wood
					Color(147, 88, 28),
					Color(127, 73, 18),
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

Floor::~Floor()
{
}
