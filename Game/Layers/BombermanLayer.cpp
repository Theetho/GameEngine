#include "pch.h"
#include "BombermanLayer.h"
#include "Util/FileLoader.h"

using namespace Engine;

BombermanLayer::BombermanLayer()
	: mPlayer(AssetManager::GetModelLibrary().Load("varyasuit/DolBarriersuit.obj", "player"))
	, mCamera(mPlayer, 6.0f)
	, mSkybox("Skyboxes/Day")
{
}

BombermanLayer::~BombermanLayer()
{}

void BombermanLayer::OnAttach()
{
	mMap = FileLoader::LoadMap("AsSets/MapFiles/map_1.map");

	AssetManager::GetModelLibrary().Load("sphere/sphere.obj", "bomb");

	mPlayer.SetPosition(mMap->GetEntry());
	mPlayer.SetScale(0.05f);

	mLights.push_back(
		std::make_shared<DirectionalLight>(Vec3(0.5f, -0.5f, 0.0f))
	);
	
	Ref<Shader> shader = AssetManager::GetShaderLibrary().Load("lights_materials.glsl", "scene");
	Ref<Shader> shader_pbr = AssetManager::GetShaderLibrary().Load("lights_PBR.glsl", "player");
	AssetManager::GetShaderLibrary().Load("skybox.glsl", "skybox");

	for (int i = 0; i < mLights.size(); ++i)
	{
		mLights[i]->Load(shader, i);
		mLights[i]->Load(shader_pbr, i);
	}

	RenderCommand::SetClearColor(Color::Black);
	Input::ToggleCursor();
}

void BombermanLayer::OnDetach()
{}

void BombermanLayer::OnUpdate(
	const double& delta
)
{
	mPlayer.OnUpdate(delta);
	mCamera.OnUpdate(delta);
	mMap->OnUpdate(delta, mBombs.size() == 0);

	while(mPlayer.GetBombs().size())
	{
		auto bomb = mPlayer.GetBombs()[mPlayer.GetBombs().size() - 1];
		bomb->GetSurroundingWalls(*mMap);
		mBombs.push_back(bomb);
		mPlayer.GetBombs().pop_back();
	}
	
	RenderCommand::Clear();

	Ref<Shader> shader = AssetManager::GetShaderLibrary().Get("scene");
	Ref<Shader> shader_pbr = AssetManager::GetShaderLibrary().Get("player");
	Ref<Shader> shader_skybox = AssetManager::GetShaderLibrary().Get("skybox");

	Renderer::BeginScene(mCamera, shader_pbr);

	for (auto wall : mMap->GetWalls())
		Renderer::Submit(*wall.GetModel(), wall.GetTransform());

	for (auto wall : mMap->GetDestructibleWalls())
	{
		if (wall.IsEnabled())
		{
			Renderer::Submit(*wall.GetModel(), wall.GetTransform());
		}
	}

	for (auto floor : mMap->GetFloor())
		Renderer::Submit(*floor.GetModel(), floor.GetTransform());
	
	Renderer::Submit(*mMap->GetExit().GetModel(), mMap->GetExit().GetTransform());

	Renderer::Submit(*mPlayer.GetModel(), mPlayer.GetTransform());

	Renderer::EndScene();
	
	Renderer::BeginScene(mCamera, shader);
	
	auto bomb = mBombs.begin();
	for (size_t i = 0; i < mBombs.size();)
	{
		if (mBombs[i]->hasExploded)
		{
			mBombs.erase(bomb);
			continue;
		}
		
		mBombs[i]->OnUpdate(delta);
		Renderer::Submit(mBombs[i]->GetModel(), mBombs[i]->GetTransform());
		++i; ++bomb;
	}
	
	Renderer::EndScene();
	
	Renderer::BeginScene(mCamera, shader_skybox);
	
	Renderer::Submit(mSkybox);

	Renderer::EndScene();
}

void BombermanLayer::OnEvent(
	Engine::Event & event
)
{
	mCamera.OnEvent(event);
	mPlayer.OnEvent(event);
}
