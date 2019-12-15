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
{
}

Map::~Map()
{
}

void Map::onUpdate(
	const double& delta
)
{
	m_destructibleWalls.erase(
		std::remove_if(
			m_destructibleWalls.begin(),
			m_destructibleWalls.end(),
			[](const DestructibleWall& wall)
			{
				return wall.hasExploded;
			}
		),
		m_destructibleWalls.end()
	);
}
