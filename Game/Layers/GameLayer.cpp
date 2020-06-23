#include "pch.h"
#include "GameLayer.h"

using namespace Engine;

GameLayer::GameLayer()
	: mCube()
	, mClearColor(Color::Aqua)
{}

GameLayer::~GameLayer()
{}

void GameLayer::OnAttach()
{
	mCube.LoadMesh("../Engine/Assets/Models/Bob/boblampclean.md5mesh");
	auto animator = mCube.AddComponent<Animator>(mCube.GetMesh());
	animator->SetCurrentAnimation(0);
	mCube.GetTransform().SetPosition(Vec3(0.f));
	mCube.GetTransform().SetRotation('x', -90.0f);
	mCube.GetTransform().SetScale(0.2f);

	mCube2.LoadMesh("../Engine/Assets/Models/THM/model.dae");
	(void)mCube2.AddComponent<Animator>(mCube2.GetMesh());
	mCube2.GetTransform().SetPosition(Vec3(0.f, 0.f, 5.0f));
	mCube2.GetTransform().SetRotation('x', -90.0f);

	mCube3.LoadMesh("../Engine/Assets/Models/Character/model.dae");
	mCube3.GetTransform().SetPosition(Vec3(5.f, 0.f, 0.f));
	mCube3.GetTransform().SetRotation('x', -90.0f);
	mCube3.GetTransform().SetScale(2.0f);

	(void)AssetManager::GetShaderLibrary().Load("../Engine/Assets/Shaders/lights_materials.glsl", "shader", false);
	(void)AssetManager::GetShaderLibrary().Load("../Engine/Assets/Shaders/lights_PBR.glsl", "PBR", false);

	Application::Get()->GetScene().AddLight(CreateRef<DirectionalLight>(Vec3(1.0, -1.0, 0.0)));

	RenderCommand::SetClearColor(mClearColor);
}

void GameLayer::OnDetach()
{}

void GameLayer::OnUpdate(Ref<Camera3D> camera, const double& delta)
{
	auto shader = AssetManager::GetShaderLibrary().Get("shader");
	auto pbr    = AssetManager::GetShaderLibrary().Get("PBR");
	
	camera->OnUpdate(delta);
	mCube.OnUpdate(delta);
	mCube2.OnUpdate(delta);
	mCube3.OnUpdate(delta);

	RenderCommand::Clear();

	Renderer::BeginScene(camera);
	Renderer::Submit(pbr, mCube);
	Renderer::Submit(pbr, mCube2);
	Renderer::Submit(shader, mCube3);
	
	Renderer::Render();
	Renderer::EndScene();
}

void GameLayer::OnEvent(Engine::Event& event)
{
}

void GameLayer::OnEngineGui()
{
	auto left_panel = Application::Get()->GetEngineGUI().GetPanel("Left");
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
