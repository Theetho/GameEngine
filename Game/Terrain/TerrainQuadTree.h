#pragma once

#include "Util/Node.h"
#include "TerrainConfiguration.h"

class TerrainQuadTree : public Node
{
public:
	TerrainQuadTree(const TerrainConfiguration& configuration);
	~TerrainQuadTree();

	void OnUpdate(const double& delta) override;

	static unsigned int GetRootNodesCount();
private:
	static const unsigned int sRootNodes;

	std::vector<float> GenerateVertices() const;
};

