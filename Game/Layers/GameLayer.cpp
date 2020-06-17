#include "pch.h"
#include "GameLayer.h"

using namespace Engine;

GameLayer::GameLayer()
	: mCube()
	, mScene()
	, mClearColor(Color::Aqua)
{}

GameLayer::~GameLayer()
{}

void GameLayer::OnAttach()
{
	//mCube.SetMaterial(CreateRef<RawMaterial>(RawMaterial::Bronze));
	mCube.GetTransform().SetPosition(Vec3(0.f));
	mCube.GetTransform().SetRotation('x', -90.0f);

	mScene.Push(&mCube);

	auto shader = AssetManager::GetShaderLibrary().Load("../Engine/Assets/Shaders/lights_materials.glsl", "shader", false);

	mScene.GetLights().push_back(CreateRef<DirectionalLight>(Vec3( 1.0, -1.0,  0.0), Color(0.3f)));
	/*mScene.GetLights().push_back(CreateRef<DirectionalLight>(Vec3(-1.0, -1.0,  0.0), Color(0.4f)));
	mScene.GetLights().push_back(CreateRef<DirectionalLight>(Vec3( 0.0, -1.0, -1.0), Color(0.4f)));
	mScene.GetLights().push_back(CreateRef<DirectionalLight>(Vec3( 0.0, -1.0,  1.0), Color(0.4f)));*/

	RenderCommand::SetClearColor(mClearColor);
}

void GameLayer::OnDetach()
{}

void GameLayer::OnUpdate(Ref<Camera3D> camera, const double& delta)
{
	auto shader = AssetManager::GetShaderLibrary().Get("shader");
	mScene.UpdateLights({shader});

	camera->OnUpdate(delta);

	RenderCommand::Clear();

	Renderer::BeginScene(camera);
	Renderer::Submit(shader, mCube);
	
	Renderer::Render();
	Renderer::EndScene();
}

void GameLayer::OnEvent(Engine::Event& event)
{
}

void GameLayer::OnEngineGui()
{
	mScene.Render();

	auto left_panel = Application::Get().GetEngineGUI().GetPanel("Left");
	auto tab = left_panel.GetOpenedTab();
	static bool clear_color = false;
	
	if (tab == Tab::Scene)
	{
		left_panel.Begin();
		if (ImGui::TreeNode("Clear color"))
		{
			ImGui::ColorEdit3("", (float*)&mClearColor);
			RenderCommand::SetClearColor(mClearColor);
			ImGui::TreePop();
		}
		left_panel.End();
	}
}

void GameLayer::OnGui()
{
}
