#include "pch.h"
#include "BombermanLayer.h"
#include "Util/FileLoader.h"

using namespace Engine;

BombermanLayer::BombermanLayer()
	: mPlayer(AssetManager::GetModelLibrary().Load("varyasuit/DolBarriersuit.obj", "player"))
	, mCamera(mPlayer, 8.0f)
	//, mCamera(Vec3(100.0f, 20.0f, 100.0f))
	, mSkybox("Skyboxes/Day")
	, mTerrain(Vec2(0, 0), "Heightmaps/generated_height_map.png", Vec2(200))
	, mLake(Vec3(0.0f, 0.45f * 5.0f + 1.0f, 0.0f), Vec2(200))
	, mRefraction(Vec2(-0.5, 0.5), Vec2(0.25, 0.25), mLake.GetRefractionBuffer()->GetTextureAttachment())
	, mReflection(Vec2(0.5,  0.5), Vec2(0.25, 0.25), mLake.GetReflectionBuffer()->GetTextureAttachment())
{
}

BombermanLayer::~BombermanLayer()
{}

void BombermanLayer::OnAttach()
{
	(void)AssetManager::GetModelLibrary().Load("sphere/sphere.obj", "bomb");

	mPlayer.SetPosition(Vec3(100, 100, 100));
	mPlayer.SetScale(0.05f);

	mLights.push_back(
		CreateRef<DirectionalLight>(Vec3(0.4f, -0.5f, 0.0f))
	);
	
	Ref<Shader> shader		   = AssetManager::GetShaderLibrary().Load("lights_materials.glsl", "scene");
	Ref<Shader> shader_pbr	   = AssetManager::GetShaderLibrary().Load("lights_PBR.glsl", "player");
	Ref<Shader> shader_terrain = AssetManager::GetShaderLibrary().Load("terrain.glsl");
	Ref<Shader> shader_water   = AssetManager::GetShaderLibrary().Load("water.glsl");
	(void)AssetManager::GetShaderLibrary().Load("skybox.glsl");
	(void)AssetManager::GetShaderLibrary().Load("colliders.glsl");
	(void)AssetManager::GetShaderLibrary().Load("gui.glsl");

	for (int i = 0; i < mLights.size(); ++i)
	{
		mLights[i]->Load(shader, i);
		mLights[i]->Load(shader_pbr, i);
		mLights[i]->Load(shader_terrain, i);
		mLights[i]->Load(shader_water, i);
	}

	RenderCommand::SetClearColor(Color(0, 200, 255));
	Input::ToggleCursor();
}

void BombermanLayer::OnDetach()
{}

void BombermanLayer::OnUpdate(const double& delta)
{
	mPlayer.OnUpdate(delta);
	mCamera.OnUpdate(delta);
	mLake  .OnUpdate(delta);
	
	Ref<Shader> shader			= AssetManager::GetShaderLibrary().Get("scene");
	Ref<Shader> shader_pbr		= AssetManager::GetShaderLibrary().Get("player");
	Ref<Shader> shader_terrain	= AssetManager::GetShaderLibrary().Get("terrain");
	Ref<Shader> shader_skybox   = AssetManager::GetShaderLibrary().Get("skybox");
	Ref<Shader> shader_collider = AssetManager::GetShaderLibrary().Get("colliders");
	Ref<Shader> shader_water    = AssetManager::GetShaderLibrary().Get("water");
	Ref<Shader> shader_gui      = AssetManager::GetShaderLibrary().Get("gui");
	
	Renderer::BeginScene(mCamera);
	RenderCommand::Clear();

	Renderer::Submit(shader_terrain, mTerrain);
	Renderer::Submit(shader_pbr,     mPlayer);
	Renderer::Submit(shader_skybox,  mSkybox);
	
	Renderer::PrepareWater(mCamera, mLake);
	
	//Renderer::Submit(shader_gui, mRefraction);
	//Renderer::Submit(shader_gui, mReflection);
	Renderer::Submit(shader_water, mLake);
	Renderer::Render();
	Renderer::EndScene();
}

void BombermanLayer::OnEvent(Engine::Event & event)
{
	mCamera.OnEvent(event);
	mPlayer.OnEvent(event);
}

/// FOR BOMBERMAN GAME

	//mMap = FileLoader::LoadMap("Assets/MapFiles/map_1.map");
	//mPlayer.SetPosition(mMap->GetEntry());
	
	//mMap->OnUpdate(delta, mBombs.size() == 0);
	//
	//while(mPlayer.GetBombs().size())
	//{
	//	auto bomb = mPlayer.GetBombs()[mPlayer.GetBombs().size() - 1];
	//	bomb->GetSurroundingWalls(*mMap);
	//	mBombs.push_back(bomb);
	//	mPlayer.GetBombs().pop_back();
	//}
	//Renderer::Submit(shader_pbr, *mMap);
	//auto bomb = mBombs.begin();
	//for (size_t i = 0; i < mBombs.size();)
	//{
	//	if (mBombs[i]->hasExploded)
	//	{
	//		mBombs.erase(bomb);
	//		continue;
	//	}
	//	
	//	mBombs[i]->OnUpdate(delta);
	//	Renderer::Submit(shader, *mBombs[i]);
	//	++i; ++bomb;
	//}	