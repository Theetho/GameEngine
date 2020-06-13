#include "pch.h"
#include "FileLoader.h"

Engine::Scope<Map> FileLoader::LoadMap(const std::string& file_path)
{
	unsigned int height, width;
	float size = 1.0f;

	std::ifstream file(file_path, std::ios::in, std::ios::binary);
	std::string line;
	
	if (!file)
	{
		APP_LOG_WARN("Can't open '{0}'; Default map loaded.", file_path);
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

	float origin_x = - (float)width  / 2.0f;
	float origin_y =          size   / 2.0f;
	float origin_z = - (float)height / 2.0f;
	float step     = size;
	unsigned int line_index = 0, column_index = 0;

	while (std::getline(file, line))
	{
		for (char digit : line)
		{
			Engine::Vec3 scale(size, 0.5f ,size);

			Engine::Vec3 position(
				origin_x + (column_index * step),
				- origin_y * scale.y,
				origin_z + (line_index * step)
			);

			switch (digit)
			{
			case '0':
				map->AddFloor(Floor(Engine::Transform(position, {}, scale)));

				break;

			case '1':
				position.y = - position.y;
				
				map->AddWalls(Wall(Engine::Transform(position, {}, scale)));

				break;

			case '2':
				map->AddFloor(Floor(Engine::Transform(position, {}, scale)));
				
				position.y = - position.y;

				map->AddWalls(DestructibleWall(Engine::Transform(position, {}, scale)));

				break;

			case 'i':
				map->AddFloor(Floor(Engine::Transform(position, {}, scale)));

				map->SetEntry(map->GetFloor().back().GetTransform().GetPosition() + Engine::Vec3(0.0f, size, 0.0f));

				break;

			case 'o':
				map->AddFloor(ExitCell(Engine::Transform(position, {}, scale)));

				position.y = -position.y;

				map->AddWalls(DestructibleWall(Engine::Transform(position, {}, scale)));

				break;

			default:
				break;
			}

			++column_index;
		}
		++line_index;
		column_index = 0;
	}

	file.close();

	return map;
}
