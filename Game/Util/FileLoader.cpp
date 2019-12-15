#include "pch.h"
#include "FileLoader.h"

Engine::Scope<Map> FileLoader::loadMap(
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
		file.open("Assets/MapFiles/default.map");
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

	Engine::Scope<Map> map = std::make_unique<Map>(width, height, Engine::Vec3(size));

	float originX = - (float)width  / 2.0f;
	float originY =          size   / 2.0f;
	float originZ = - (float)height / 2.0f;
	float step    = size;
	unsigned int lineIndex = 0, columnIndex = 0;

	while (std::getline(file, line))
	{
		for (char digit : line)
		{
			Engine::Vec3 scale(size, 0.5f ,size);

			Engine::Vec3 position(
				originX + (columnIndex * step),
				- originY * scale.y,
				originZ + (lineIndex * step)
			);

			switch (digit)
			{
			case '0':
				map->addFloor(Floor(Engine::Transform(position, {}, scale)));

				break;

			case '1':
				position.y = - position.y;
				
				map->addWalls(Wall(Engine::Transform(position, {}, scale)));

				break;

			case '2':
				map->addFloor(Floor(Engine::Transform(position, {}, scale)));
				
				position.y = - position.y;

				map->addWalls(DestructibleWall(Engine::Transform(position, {}, scale)));

				break;

			case 'i':
				map->addFloor(Floor(Engine::Transform(position, {}, scale)));

				map->setEntry(map->getFloor().back().getTransform().getPosition() + Engine::Vec3(0.0f, size, 0.0f));

				break;

			case 'o':
				map->addFloor(ExitCell(Engine::Transform(position, {}, scale)));

				position.y = -position.y;

				map->addWalls(DestructibleWall(Engine::Transform(position, {}, scale)));

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

	return map;
}
