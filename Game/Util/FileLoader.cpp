#include "pch.h"
#include "FileLoader.h"

Engine::Scope<Maze> FileLoader::loadMaze(
	const std::string& filePath
)
{
	unsigned int height, width;
	float size = 1.0f;

	std::ifstream file(filePath, std::ios::in, std::ios::binary);
	std::string line;
	
	if (!file)
	{
		APP_LOG_WARN("Can't open '{0}'; Default map loaded.", filePath);
		file.open("Assets/MazeFiles/default.mz");
	}

	// Get the first line (format : "height width")
	std::getline(file, line);
	// Find the space between height and width
	auto space = line.find_first_of(' ');
	// space position = '|' -> height| width
	height = std::atoi((line.substr(0, space)).c_str());
	space += 1;
	// space position = '|' -> height |width
	width = std::atoi((line.substr(space, line.size() - space)).c_str());

	Engine::Scope<Maze> maze(new Maze(width, height));

	float originX = - (float)width  / 2.0f;
	float originY =          size   / 2.0f;
	float originZ = - (float)height / 2.0f;
	float step    = size;
	unsigned int lineIndex = 0, columnIndex = 0;

	while (std::getline(file, line))
	{
		for (char digit : line)
		{
			Engine::Vec3 position(
				originX + (columnIndex * step),
				- originY,
				originZ + (lineIndex * step)
			);

			switch (digit)
			{
			case '0':
				maze->addGround(Cube(size, Engine::Transform(position)));

				break;

			case '1':
				position.y = -position.y;
				
				maze->addWalls(Cube(size, Engine::Transform(position)));

				break;

			case 'i':
				maze->addGround(Cube(size, Engine::Transform(position)));

				maze->setEntry(maze->getGround().back().getTransform().getPosition() + Engine::Vec3(0.0f, size, 0.0f));

				break;

			case 'o':
				maze->addGround(Cube(size, Engine::Transform(position)));

				maze->setExit(maze->getGround().back().getTransform().getPosition() + Engine::Vec3(0.0f, size, 0.0f));

				break;

			default:
				break;
			}
			++columnIndex;
		}
		++lineIndex;
		columnIndex = 0;
	}

	file.close();

	return maze;
}
