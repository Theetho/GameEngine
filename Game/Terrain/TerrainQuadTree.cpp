#include "pch.h"
#include "TerrainQuadTree.h"
#include "TerrainNode.h"
#include "../PatchVertexArray.h"

using namespace Engine;

const unsigned int TerrainQuadTree::sRootNodes = 8;

TerrainQuadTree::TerrainQuadTree(const TerrainConfiguration& configuration)
{
	PatchVertexArray pvao;
	auto vertices = this->GenerateVertices();
	auto vbo = VertexBuffer::Create(vertices.data(), vertices.size());
	vbo->SetLayout(BufferLayout({
		BufferElement(ShaderDataType::Float2, "inPosition")
	}));
	pvao.AddVertexBuffer(vbo);
	
	for (unsigned int i = 0; i < sRootNodes; ++i)
	{
		for (unsigned int j = 0; j < sRootNodes; ++j)
		{
			AddChild(new TerrainNode(pvao, configuration, Vec2(i, j) / (float)sRootNodes, 0, Vec2(i, j)));
		}
	}

	mGlobalTransform.SetScale(Vec3(configuration.GetScaleXZ(), configuration.GetScaleY(), configuration.GetScaleXZ()));
	mLocalTransform.SetScale(mGlobalTransform.GetScale() / 2.0f);
	mLocalTransform.SetScale('y', 0.0f);
}

TerrainQuadTree::~TerrainQuadTree()
{}

void TerrainQuadTree::OnUpdate(const double& delta)
{
	for (auto child : mChildren)
	{

	}
}

unsigned int TerrainQuadTree::GetRootNodesCount()
{
	return sRootNodes;
}

std::vector<float> TerrainQuadTree::GenerateVertices() const
{
	std::vector<float> vertices;

	for (unsigned int i = 0; i < 4; ++i)
	{
		for (unsigned int j = 0; j < 4; ++j)
		{
			vertices.push_back((float)(i % 4) / 3.0f);
			vertices.push_back((float)(j % 4) / 3.0f);
		}
	}

	return vertices;
}
