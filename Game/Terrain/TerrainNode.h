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
private:
	bool mIsLeaf;
	const TerrainConfiguration& mTerrainConfiguration;
	unsigned int mLod;
	Engine::Vec2 mLocation;
	Engine::Vec3 mPosition;
	Engine::Vec2 mIndex;
	float mGap;
	PatchVertexArray mVertexArray;

	void Render(Engine::Ref<Engine::RenderCommand> render_command, Engine::Ref<Engine::Shader> shader) const override;
};

