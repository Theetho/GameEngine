#pragma once

#include "Util/Node.h"
#include "TerrainConfiguration.h"

class Terrain : public Node
{
public:
	Terrain(const std::string& config_file);
	~Terrain();

	void OnUpdate(const double& delta) override;
private:
	TerrainConfiguration mTerrainConfiguration;
};

