#include "pch.h"
#include "TerrainLayer.h"

using namespace Engine;

TerrainLayer::TerrainLayer()
	: mCamera(Vec3(100.0f, 500.0f, 100.0f))
	, mTerrain("./Assets/TerrainConfig.txt")
	, mSkybox("/Skyboxes/Day")
{}

TerrainLayer::~TerrainLayer()
{}

void TerrainLayer::OnAttach()
{
	mLights = {
		CreateRef<DirectionalLight>(Vec3(0.4, -0.5f, 0.0f))
	};

	(void)AssetManager::GetShaderLibrary().Load("skybox.glsl");
	auto terrain_shader = AssetManager::GetShaderLibrary().Load("TessTerrain.glsl");

	mTerrain.Load(terrain_shader);

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

	Ref<Shader> terrain_shader = AssetManager::GetShaderLibrary().Get("TessTerrain");
	Ref<Shader> skybox_shader  = AssetManager::GetShaderLibrary().Get("skybox");

	RenderCommand::Clear();
	Renderer::BeginScene(mCamera);
	Renderer::Submit(terrain_shader, mTerrain);
	Renderer::Submit(skybox_shader , mSkybox);
	Renderer::Render();
	Renderer::EndScene();
}

void TerrainLayer::OnEvent(Engine::Event& event)
{
	mCamera.OnEvent(event);
	if (event.mType == Event::Type::KeyReleased)
	{
		if (event.mKeyEvent.code == ENGINE_KEY_Z)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else if (event.mKeyEvent.code == ENGINE_KEY_X)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}