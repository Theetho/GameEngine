#include "pch.h"
#include "BombermanLayer.h"

using namespace Engine;

BombermanLayer::BombermanLayer()
	: mCamera(Vec3(100.0f, 20.0f, 100.0f))
	, mSkybox("Skyboxes/Day")
	, mTerrain(Vec2(0, 0), "Heightmaps/generated_height_map.png", Vec2(200))
	, mLake(Vec3(0.0f, 0.45f * 5.0f + 2.0f, 0.0f), Vec2(200))
	/*, mFont("./Assets/Fonts/consola.ttf", 48)
	, mGui(Vec2(0, 0), Vec2(0.5, 0.5))*/
{}

BombermanLayer::~BombermanLayer()
{}

void BombermanLayer::OnAttach()
{
	(void)AssetManager::GetModelLibrary().Load("sphere/sphere.obj", "bomb");

	mCamera.AddComponent<RigidBody3D>(CreateRef<RigidBody3D>(mCamera));
	mCamera.AddComponent<Movement3D>(CreateRef<Movement3D>(mCamera, true));

	mLights = {
		CreateRef<DirectionalLight>(Vec3( 0.4, -0.5f, 0.0f))
	};
	
	/*Text::SetGlobalFont(&mFont);
	mText = Text("Ceci est une chaine test", { -1.0, 0.0 }, Color::Brown);*/
	
	/*Ref<Texture2D> gui_texture = AssetManager::GetTexture2DLibrary().Load("snow.jpg");
	mGui.SetTexture(gui_texture);*/

	Ref<Shader> shader		   = AssetManager::GetShaderLibrary().Load("lights_materials.glsl", "scene");
	Ref<Shader> shader_pbr	   = AssetManager::GetShaderLibrary().Load("lights_PBR.glsl", "player");
	Ref<Shader> shader_terrain = AssetManager::GetShaderLibrary().Load("terrain.glsl");
	(void)AssetManager::GetShaderLibrary().Load("skybox.glsl");
	(void)AssetManager::GetShaderLibrary().Load("colliders.glsl");
	(void)AssetManager::GetShaderLibrary().Load("gui.glsl");
	(void)AssetManager::GetShaderLibrary().Load("text.glsl");
	(void)AssetManager::GetShaderLibrary().Load("Skybox_Colored.glsl");
	Ref<OpenGL::Shader> shader_water = std::dynamic_pointer_cast<OpenGL::Shader>(AssetManager::GetShaderLibrary().Load("water.glsl"));

	for (int i = 0; i < mLights.size(); ++i)
	{
		mLights[i]->Load(shader, i);
		mLights[i]->Load(shader_pbr, i);
		mLights[i]->Load(shader_terrain, i);
		mLights[i]->Load(shader_water, i);
	}

	shader_water->UploadUniform("uNear", mCamera.Near);
	shader_water->UploadUniform("uFar" , mCamera.Far);

	RenderCommand::SetClearColor(Color(0, 200, 255));
}

void BombermanLayer::OnDetach()
{}

void BombermanLayer::OnUpdate(const double& delta)
{
	//mPlayer.OnUpdate(delta);
	mCamera.OnUpdate(delta);
	mLake  .OnUpdate(delta);
	
	Ref<Shader> shader				  = AssetManager::GetShaderLibrary().Get("scene");
	Ref<Shader> shader_pbr			  = AssetManager::GetShaderLibrary().Get("player");
	Ref<Shader> shader_terrain		  = AssetManager::GetShaderLibrary().Get("terrain");
	Ref<Shader> shader_skybox		  = AssetManager::GetShaderLibrary().Get("skybox");
	Ref<Shader> shader_skybox_colored = AssetManager::GetShaderLibrary().Get("Skybox_Colored");
	Ref<Shader> shader_collider		  = AssetManager::GetShaderLibrary().Get("colliders");
	Ref<Shader> shader_water		  = AssetManager::GetShaderLibrary().Get("water");
	Ref<Shader> shader_gui			  = AssetManager::GetShaderLibrary().Get("gui");
	Ref<Shader> shader_text			  = AssetManager::GetShaderLibrary().Get("text");
	
	
	RenderCommand::Clear();

	Renderer::Submit(shader_terrain, mTerrain);
	Renderer::Submit(shader_skybox, mSkybox);
	
	Renderer::PrepareWater(mCamera, mLake);

	Renderer::BeginScene(mCamera);
	Renderer::Submit(shader_water, mLake);
	/*Renderer::Submit(shader_gui, mGui);
	Renderer::Submit(shader_text, mText);*/
	Renderer::Render();
	Renderer::EndScene();
}

void BombermanLayer::OnEvent(Engine::Event & event)
{
	mCamera.OnEvent(event);
}

void BombermanLayer::OnGui()
{}

void BombermanLayer::OnEngineGui()
{}

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
