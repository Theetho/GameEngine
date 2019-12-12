#include "pch.h"
#include "Map.h"

using namespace Engine;

Map::Map(
	const unsigned int& width,
	const unsigned int& height,
	const Vec3& blockSize
)
	: m_width(width)
	, m_height(height)
	, m_blockSize(blockSize)
	, m_entry()
	, m_exit()
{
}

Map::~Map()
{
}

void Map::addCollider(
	Ref<GameObject> object
)
{
	object->AddComponent<BoxCollider>(std::make_shared<BoxCollider>(
		*object, object->getTransform().getPosition(),
		m_blockSize.x, m_blockSize.y, m_blockSize.z));
}
