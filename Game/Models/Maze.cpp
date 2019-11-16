#include "pch.h"
#include "Maze.h"

Maze::Maze(
	const unsigned int& width,
	const unsigned int& height,
	const Engine::Vec3& blockSize
)
	: m_width(width)
	, m_height(height)
	, m_blockSize(blockSize)
	, m_entry()
	, m_exit()
{
	// Load the cube model to display the maze parts
	Engine::AssetManager::getModelLibrary().load("cube/cube.obj", "cube");
}

Maze::~Maze()
{
}

void Maze::addCollider(
	Engine::Ref<Engine::GameObject> object
)
{
	object->AddComponent<Engine::BoxCollider>(
		std::make_shared<Engine::BoxCollider>(
			*object,
			object->getTransform().getPosition(),
			m_blockSize.x, m_blockSize.y, m_blockSize.z
		)
	);
}
