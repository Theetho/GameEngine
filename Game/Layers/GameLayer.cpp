#include "pch.h"
#include "GameLayer.h"

using namespace Engine;

GameLayer::GameLayer()
	: mClearColor(Color::Aqua)
	, mCamera(0.0f, 0.0f, 0.0f, 0.0f)
{
	float aspect_ratio = Application::Get()->GetWindow().GetWidth() / Application::Get()->GetWindow().GetHeight();
	mCamera.SetProjection(-aspect_ratio, aspect_ratio, -1.0f, 1.0f);
}

GameLayer::~GameLayer()
{}

void GameLayer::OnAttach()
{
	RenderCommand::SetClearColor(mClearColor);

	float factor = 8.f;
	
	Vec2 quad_size(2.0f / factor, 2.0f / factor);
	Ref<Texture2D> colors[4] = {
		AssetManager::GetTexture2DLibrary().Load("../Sandbox/Assets/Textures/Skyboxes/Day/1 - right.jpg", "right", false),
		AssetManager::GetTexture2DLibrary().Load("../Sandbox/Assets/Textures/Skyboxes/Day/2 - left.jpg", "left", false),
		AssetManager::GetTexture2DLibrary().Load("../Sandbox/Assets/Textures/Skyboxes/Day/3 - top.jpg", "top", false),
		AssetManager::GetTexture2DLibrary().Load("../Sandbox/Assets/Textures/Skyboxes/Day/6 - back.jpg", "back", false)
	};
	uint i = 0;
	
	auto scene = Application::Get()->GetScene();

	for (int x = 0; x < factor; ++x) {
		for (int y = 0; y < factor; ++y) {
			auto object = scene->AddObject<GameObject<2>>();// Instanciator::Create<GameObject2D>();//GameObject2D::Create();
			object->AddComponent<Sprite>(colors[(x + y) % 4]);
	
			Vec2 position = (Vec2(x, y) / factor) * 2.0f;
			
			auto transform = object->GetComponent<Transform2D>();

			transform->SetPosition(position);
			transform->SetScale(quad_size);
			// object->SetShowOnEditor(false);
	
			mObjects.push_back(object);
		}
	}

	Application::Get()->GetScene()->AddLight<DirectionalLight>(Vec3(1.0));
}

void GameLayer::OnDetach()
{}

void GameLayer::OnUpdate(Ref<Camera3D> camera, const double& delta)
{
	RenderCommand::Clear();
	mRenderer.Begin(mCamera);

	for (auto& object : mObjects) {
		mRenderer.Submit(object);
	}
	// mRenderer.Submit(&mObject);

	mRenderer.End();
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
