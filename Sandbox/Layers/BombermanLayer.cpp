#include "pch.h"
#include "BombermanLayer.h"

using namespace Engine;

BombermanLayer::BombermanLayer()
	: mSkybox("Skyboxes/Day")
	, mTerrain(Vec2(-0.5f, -0.5f), "Heightmaps/generated_height_map.png", Vec2(200))
	, mLake(Vec3(-100.0f, 0.45f * 5.0f + 2.0f, -100.0f), Vec2(200))
{}

BombermanLayer::~BombermanLayer()
{}

void BombermanLayer::OnAttach()
{
	Ref<Shader> shader		   = AssetManager::GetShaderLibrary().Load("lights_materials.glsl", "scene");
	Ref<Shader> shader_pbr	   = AssetManager::GetShaderLibrary().Load("lights_PBR.glsl", "player");
	Ref<Shader> shader_terrain = AssetManager::GetShaderLibrary().Load("terrain.glsl");
	(void)AssetManager::GetShaderLibrary().Load("skybox.glsl");
	(void)AssetManager::GetShaderLibrary().Load("colliders.glsl");
	(void)AssetManager::GetShaderLibrary().Load("gui.glsl");
	(void)AssetManager::GetShaderLibrary().Load("text.glsl");
	(void)AssetManager::GetShaderLibrary().Load("Skybox_Colored.glsl");
	Ref<OpenGL::Shader> shader_water = std::dynamic_pointer_cast<OpenGL::Shader>(AssetManager::GetShaderLibrary().Load("water.glsl"));

	mScene.GetLights().push_back(CreateRef<DirectionalLight>(Vec3(0.4, -0.5f, 0.0f)));
	mScene.GetLights().push_back(CreateRef<SpotLight>(Vec3(0.0, 1.0, 0.0), Vec3(0.0, -1.0, 0.0)));

	mScene.UpdateLights({
		shader,
		shader_pbr,
		shader_terrain,
		shader_water
	});

	auto& playing_panel = Application::Get().GetEngineGUI().GetPanel("Playing");

	mScene.Push(&mLake);
	mScene.Push(&mTerrain);

	RenderCommand::SetClearColor(mClearColor);
}

void BombermanLayer::OnDetach()
{}

void BombermanLayer::OnUpdate(Ref<Camera3D> camera, const double& delta)
{
	camera->OnUpdate(delta);
	mLake  .OnUpdate(delta);
	
	Ref<Shader> shader				  = AssetManager::GetShaderLibrary().Get("scene");
	Ref<Shader> shader_pbr			  = AssetManager::GetShaderLibrary().Get("player");
	Ref<Shader> shader_terrain		  = AssetManager::GetShaderLibrary().Get("terrain");
	Ref<Shader> shader_skybox		  = AssetManager::GetShaderLibrary().Get("skybox");
	Ref<Shader> shader_skybox_colored = AssetManager::GetShaderLibrary().Get("Skybox_Colored");
	Ref<Shader> shader_collider		  = AssetManager::GetShaderLibrary().Get("colliders");
	Ref<OpenGL::Shader> shader_water  = std::dynamic_pointer_cast<OpenGL::Shader>(AssetManager::GetShaderLibrary().Get("water"));
	Ref<Shader> shader_gui			  = AssetManager::GetShaderLibrary().Get("gui");
	Ref<Shader> shader_text			  = AssetManager::GetShaderLibrary().Get("text");
	
	mScene.UpdateLights({
		shader,
		shader_pbr,
		shader_terrain,
		shader_water
	});

	shader_water->Bind();
	shader_water->UploadUniform("uNear", camera->GetNear());
	shader_water->UploadUniform("uFar", camera->GetFar());
	shader_water->Unbind();

	RenderCommand::Clear();

	Renderer::Submit(shader_terrain, mTerrain);
	if (mShowSkybox)
		Renderer::Submit(shader_skybox, mSkybox);
	else if (mShowSky)
		Renderer::Submit(shader_skybox_colored, mSkybox);

	Renderer::PrepareWater(camera, mLake);

	Renderer::BeginScene(camera);
	Renderer::Submit(shader_water, mLake);
	Renderer::Render();
	Renderer::EndScene();
}

void BombermanLayer::OnEvent(Engine::Event & event)
{
}

void BombermanLayer::OnGui()
{}

void BombermanLayer::OnEngineGui()
{
	mScene.Render();

	auto left_panel = Application::Get().GetEngineGUI().GetPanel("Left");
	auto tab = left_panel.GetOpenedTab();
	static bool clear_color = false;
	
	if (tab == Tab::Scene)
	{
		left_panel.Begin();
		if (ImGui::TreeNode("Background"))
		{
			if (ImGui::Checkbox("Texture", &mShowSkybox)) mShowSky = false;
			if (ImGui::Checkbox("Sky", &mShowSky)) mShowSkybox = false;
			ImGui::Text("Clear color");
			ImGui::ColorEdit3("", (float*)&mClearColor);
			RenderCommand::SetClearColor(mClearColor);
			ImGui::TreePop();
		}
		left_panel.End();
	}
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
