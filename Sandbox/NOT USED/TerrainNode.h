#pragma once

#include "Util/Node.h"
#include "TerrainConfiguration.h"
#include "../PatchVertexArray.h"

class TerrainNode : public Node
{
public:
	TerrainNode(const PatchVertexArray& vertex_array, const TerrainConfiguration& configuration,
		const Engine::Vec2& location, unsigned int lod, const Engine::Vec2& index);
	~TerrainNode();

	void OnUpdate(const double& delta, Engine::Camera3D& camera);
private:
	bool mIsLeaf;
	float mGap;
	unsigned int mLod;
	Engine::Vec2 mIndex;
	Engine::Vec2 mLocation;
	Engine::Vec3 mPosition;
	Engine::Transform mGlobalTransform;
	Engine::Transform mLocalTransform;
	const PatchVertexArray& mVertexArray;
	const TerrainConfiguration& mTerrainConfiguration;

	void UpdateChildren(Engine::Camera3D& camera);
	void SplitNode(unsigned int lod);
	void MergeNode();
	void ComputePosition();
	void Render(Engine::Ref<Engine::RenderCommand> render_command, Engine::Ref<Engine::Shader> shader) const override;
};

