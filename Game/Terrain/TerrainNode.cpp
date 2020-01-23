#include "pch.h"
#include "TerrainNode.h"
#include "TerrainQuadTree.h"

using namespace Engine;

TerrainNode::TerrainNode(const PatchVertexArray& vertex_array, const TerrainConfiguration& configuration,
	const Engine::Vec2& location, unsigned int lod, const Engine::Vec2& index)
	: Node()
	, mVertexArray(vertex_array)
	, mTerrainConfiguration(configuration)
	, mLocation(location)
	, mLod(lod)
	, mIndex(index)
	, mGap(1.0f /(TerrainQuadTree::GetRootNodesCount() * pow(2, lod)))
{
	mLocalTransform.SetScale({ mGap, 0.0f, mGap });
	mLocalTransform.SetPosition({ mLocation.x, 0.0f, mLocation.y });

	mGlobalTransform.SetScale({ configuration.GetScaleXZ(), configuration.GetScaleY() , configuration.GetScaleXZ() });
	mGlobalTransform.SetPosition({ - configuration.GetScaleXZ() / 2.0f, 0.0f , - configuration.GetScaleXZ() / 2.0f });
}

TerrainNode::~TerrainNode()
{}

void TerrainNode::Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const
{
	if (mIsLeaf)
	{
		Renderable::Render(&mVertexArray, render_command, shader);
	}
	else
	{
		for (auto child : mChildren)
		{
			Renderable::Render(child, render_command, shader);
		}
	}
}
