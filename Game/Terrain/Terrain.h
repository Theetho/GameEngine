#pragma once

#include "Util/Node.h"
#include "TerrainConfiguration.h"
#include "TerrainQuadTree.h"

class Terrain : public Engine::Renderable
{
public:
	Terrain(const std::string& config_file);
	~Terrain();

	void OnUpdate(const double& delta, Engine::Camera3D& camera);
private:
	TerrainConfiguration mTerrainConfiguration;
	TerrainQuadTree		 mTerrainQuadTree;

	void Render(Engine::Ref<Engine::RenderCommand> render_command, Engine::Ref<Engine::Shader> shader) const override;
};

