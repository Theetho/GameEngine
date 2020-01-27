#include "pch.h"
#include "TerrainLayer.h"

using namespace Engine;

TerrainLayer::TerrainLayer()
	: mCamera(Vec3(100.0f, 20.0f, 100.0f))
	, mTerrain("./Assets/TerrainConfig.txt")
{}

TerrainLayer::~TerrainLayer()
{}

void TerrainLayer::OnAttach()
{
	mLights = {
		CreateRef<DirectionalLight>(Vec3(0.4, -0.5f, 0.0f))
	};

	(void)AssetManager::GetShaderLibrary().Load("TessTerrain.glsl");

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//Renderer::SetDrawMode(DrawMode::PATCHES);
	RenderCommand::SetClearColor(Color(0, 200, 255));
	Input::ToggleCursor();
}

void TerrainLayer::OnDetach()
{
}

void TerrainLayer::OnUpdate(const double& delta)
{
	mCamera.OnUpdate(delta);
	mTerrain.OnUpdate(delta, mCamera);

	Ref<Shader> cTerrainShader = AssetManager::GetShaderLibrary().Get("TessTerrain");

	RenderCommand::Clear();
	Renderer::BeginScene(mCamera);
	Renderer::Submit(cTerrainShader, mTerrain);
	Renderer::Render();
	Renderer::EndScene();
}

void TerrainLayer::OnEvent(Engine::Event& event)
{
	mCamera.OnEvent(event);
}