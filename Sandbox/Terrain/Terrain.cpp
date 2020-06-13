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

void Terrain::Load(Engine::Ref<Engine::Shader> shader)
{
	switch (Engine::Renderer::GetAPI())
	{
		case Engine::API::OpenGL:
			LoadGLUniforms(std::dynamic_pointer_cast<Engine::OpenGL::Shader>(shader));
		default:
			break;
	}
}

void Terrain::Render(Engine::Ref<Engine::RenderCommand> render_command, Engine::Ref<Engine::Shader> shader) const
{
	Engine::Renderable::Render(&mTerrainQuadTree, render_command, shader);
}

void Terrain::LoadGLUniforms(Engine::Ref<Engine::OpenGL::Shader> shader)
{
	shader->Bind();
	auto morphing_areas = mTerrainConfiguration.GetLodMorphingArea();

	for (unsigned int i = 0; i < morphing_areas.size(); ++i)
	{
		shader->UploadUniform("uLodMorphingArea[" + std::to_string(i) + "]", morphing_areas[i]);
	}
	shader->Unbind();
}
