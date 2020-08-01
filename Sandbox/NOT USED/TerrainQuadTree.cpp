#include "pch.h"
#include "TerrainQuadTree.h"
#include "TerrainNode.h"
#include "../PatchVertexArray.h"

using namespace Engine;

TerrainQuadTree::TerrainQuadTree(const TerrainConfiguration& configuration, const Vec3& position)
	: Node()
	, mVertexArray()
{
	mVertexArray.AddPatch(this->GenerateVertices(), 16);
	
	for (unsigned int i = 0; i < sRootNodes; ++i)
	{
		for (unsigned int j = 0; j < sRootNodes; ++j)
		{
			AddChild(new TerrainNode(mVertexArray, configuration, Vec2(i, j) / (float)sRootNodes, 0, Vec2(i, j)));
		}
	}
}

TerrainQuadTree::~TerrainQuadTree()
{}

void TerrainQuadTree::OnUpdate(const double& delta, Engine::Camera3D& camera)
{
	for (auto child : mChildren)
	{
		static_cast<TerrainNode*>(child)->OnUpdate(delta, camera);
	}
}

int TerrainQuadTree::GetRootNodesCount()
{
	return sRootNodes;
}

std::vector<float> TerrainQuadTree::GenerateVertices() const
{
	std::vector<float> vertices;// = { -1, -1, -1, 1, 1, -1,/* 1, -1, -1, 1,*/ 1, 1 };

	for (unsigned int i = 0; i < 4; ++i)
	{
		for (unsigned int j = 0; j < 4; ++j)
		{
			vertices.push_back((float)(j % 4) / 3.0f);
			vertices.push_back((float)(i % 4) / 3.0f);
		}	
	}

	return vertices;
}
