#include "pch.h"
#include "Maze.h"

Maze::Maze(
	const unsigned int& width,
	const unsigned int& height
)
	: m_width(width)
	, m_height(height)
	, m_entry()
	, m_exit()
{
}

Maze::~Maze()
{
}