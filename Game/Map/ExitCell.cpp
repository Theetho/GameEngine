#include "pch.h"
#include "ExitCell.h"

using namespace Engine;

Ref<Model> ExitCell::s_model;
bool ExitCell::s_isInitialized = false;

ExitCell::ExitCell(
	const Transform& transform
)
	: Floor(transform)
{
	if (!s_isInitialized)
	{
		s_isInitialized = true;

		s_model = AssetManager::getModelLibrary().load("stairs/stairs.obj", "stairs");

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
	m_transform.setScale(m_transform.getScale() * 0.5f);
	m_transform.setRotation({ 0.0f, 90.0f, 0.0f });
	Vec3 size = s_model->getSize() * m_transform.getScale();

	this->AddComponent<BoxCollider>(
		std::make_shared<BoxCollider>(
			*this, m_transform.getPosition(), size.x, size.y, size.z
			)
		);
}

ExitCell::~ExitCell()
{
}