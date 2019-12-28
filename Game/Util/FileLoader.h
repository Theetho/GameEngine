#pragma once

#include "Map/Map.h"

class FileLoader
{
public:
	static Engine::Scope<Map> LoadMap(const std::string& file_path);
};

