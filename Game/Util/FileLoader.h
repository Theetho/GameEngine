#pragma once

#include "Models/Maze.h"

class FileLoader
{
public:
	static Engine::Scope<Maze> loadMaze(
		const std::string& filePath
	);
};

