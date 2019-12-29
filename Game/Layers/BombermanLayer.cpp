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
	mMap = FileLoader::LoadMap("Assets/MapFiles/map_1.map");

	AssetManager::GetModelLibrary().Load("sphere/sphere.obj", "bomb");

	mPlayer.SetPosition(mMap->GetEntry());
	mPlayer.SetScale(0.05f);

	mLights.push_back(std::make_shared<DirectionalLight>(Vec3(0.5f, -0.5f, 0.0f)));
	
	Ref<Shader> shader	   = AssetManager::GetShaderLibrary().Load("lights_materials.glsl", "scene");
	Ref<Shader> shader_pbr = AssetManager::GetShaderLibrary().Load("lights_PBR.glsl", "player");
	AssetManager::GetShaderLibrary().Load("skybox.glsl");
	AssetManager::GetShaderLibrary().Load("colliders.glsl");

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
	
	Ref<Shader> shader			= AssetManager::GetShaderLibrary().Get("scene");
	Ref<Shader> shader_pbr		= AssetManager::GetShaderLibrary().Get("player");
	Ref<Shader> shader_skybox   = AssetManager::GetShaderLibrary().Get("skybox");
	Ref<Shader> shader_collider = AssetManager::GetShaderLibrary().Get("colliders");
	
	RenderCommand::Clear();

	Renderer::BeginScene(mCamera);
	Renderer::Submit(shader_pbr, *mMap);
	Renderer::Submit(shader_pbr, mPlayer);
	
	auto bomb = mBombs.begin();
	for (size_t i = 0; i < mBombs.size();)
	{
		if (mBombs[i]->hasExploded)
		{
			mBombs.erase(bomb);
			continue;
		}
		
		mBombs[i]->OnUpdate(delta);
		Renderer::Submit(shader, *mBombs[i]);
		++i; ++bomb;
	}
	
	Renderer::Submit(shader_skybox, mSkybox);
	Renderer::Submit(shader_collider, *mPlayer.GetComponent<BoxCollider>());

	Renderer::Render();
	Renderer::EndScene();
}

void BombermanLayer::OnEvent(
	Engine::Event & event
)
{
	mCamera.OnEvent(event);
	mPlayer.OnEvent(event);
}
