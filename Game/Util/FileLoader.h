#pragma once

#include "Map/Map.h"

class FileLoader
{
public:
	static Engine::Scope<Map> loadMap(
		const std::string& filePath
	);

};

