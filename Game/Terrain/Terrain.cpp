#include "pch.h"
#include "Terrain.h"
#include "TerrainQuadTree.h"

Terrain::Terrain(const std::string& config_file)
	: mTerrainConfiguration(config_file)
{
	this->AddChild(new TerrainQuadTree());
}

Terrain::~Terrain()
{}

void Terrain::OnUpdate(const double& delta)
{
	Node::OnUpdate(delta);
}
