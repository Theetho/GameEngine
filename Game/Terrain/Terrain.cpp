#include "pch.h"
#include "Terrain.h"
#include "TerrainQuadTree.h"

Terrain::Terrain(const std::string& config_file)
	: mTerrainConfiguration(config_file)
	, mTerrainQuadTree(mTerrainConfiguration, Engine::Vec3(0))
{
}

Terrain::~Terrain()
{}

void Terrain::OnUpdate(const double& delta, Engine::Camera3D& camera)
{
	mTerrainQuadTree.OnUpdate(delta, camera);
}

void Terrain::Render(Engine::Ref<Engine::RenderCommand> render_command, Engine::Ref<Engine::Shader> shader) const
{
	Engine::Renderable::Render(&mTerrainQuadTree, render_command, shader);
}
