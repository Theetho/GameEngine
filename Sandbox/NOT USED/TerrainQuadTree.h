#pragma once

#include "Util/Node.h"
#include "TerrainConfiguration.h"
#include "../PatchVertexArray.h"

class TerrainQuadTree : public Node
{
public:
	TerrainQuadTree(const TerrainConfiguration& configuration, const Engine::Vec3& position);
	~TerrainQuadTree();

	void OnUpdate(const double& delta, Engine::Camera3D& camera);

	static int GetRootNodesCount();
private:
	static constexpr int sRootNodes = 8;
	Engine::Transform mGlobalTransform;
	Engine::Transform mLocalTransform;
	PatchVertexArray mVertexArray;

	std::vector<float> GenerateVertices() const;
};

