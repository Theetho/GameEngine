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