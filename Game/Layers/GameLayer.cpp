#include "pch.h"
#include "GameLayer.h"

using namespace Engine;

GameLayer::GameLayer()
	: mCamera(Vec3(0.0, 2.0, 2.0))
	, mCube()
	, mScene()
{}

GameLayer::~GameLayer()
{}

void GameLayer::OnAttach()
{
	mCube.SetMaterial(CreateRef<RawMaterial>(RawMaterial::Bronze));
	mCube.GetTransform().SetPosition(Vec3(0.f));

	Camera3D::Fov = 90.f;
	mCamera.AddComponent<RigidBody3D>(CreateRef<RigidBody3D>(mCamera));
	mCamera.AddComponent<Movement3D>(CreateRef<Movement3D>(mCamera, true));

	mScene.Push(&mCamera);

	auto shader = AssetManager::GetShaderLibrary().Load("../Engine/Assets/Shaders/lights_materials.glsl", "shader", false);

	mScene.GetLights().push_back(CreateRef<DirectionalLight>(Vec3(1.0, 1.0, 0.0)));
	mScene.GetLights().push_back(CreateRef<PointLight>(Vec3(-1.0, 1.0, 0.0)));
	mScene.GetLights().push_back(CreateRef<SpotLight>(Vec3(0.0, 1.0, 0.0), Vec3(0.0, -1.0, 0.0)));

	auto& playing_panel = Application::Get().GetEngineGUI().GetPanel("Playing");

	mFrameBuffer = FrameBuffer::Create(playing_panel.GetSize().x, playing_panel.GetSize().x / Camera3D::AspectRatio);
	mFrameBuffer->CreateTextureAttachment();
	mFrameBuffer->CreateRenderBuffer();

	RenderCommand::SetClearColor(Color::Black);
}

void GameLayer::OnDetach()
{}

void GameLayer::OnUpdate(const double& delta)
{
	auto shader = AssetManager::GetShaderLibrary().Get("shader");
	mScene.UpdateLights(shader);

	mCamera.OnUpdate(delta);

	if (!Application::Get().IsPlaying())
	{
		mFrameBuffer->Bind();
	}

	RenderCommand::Clear();

	Renderer::BeginScene(mCamera);
	Renderer::Submit(shader, mCube);
	
	Renderer::Render();
	Renderer::EndScene();

	if (!Application::Get().IsPlaying())
	{
		mFrameBuffer->Unbind();
	}
}

void GameLayer::OnEvent(Engine::Event& event)
{
	mCamera.OnEvent(event);
}

void GameLayer::OnEngineGui()
{
	mScene.Render();

	ImGui::ShowDemoWindow();

	// Render the scene in the playing area
	if (!Application::Get().IsPlaying())
	{
		auto playing_panel = Application::Get().GetEngineGUI().GetPanel("Playing");
		auto scene_texture = mFrameBuffer->GetTextureAttachment();

		playing_panel.Begin();
		ImGui::Image((void*)(intptr_t)scene_texture->GetId()
			, ImVec2(scene_texture->GetWidth(), scene_texture->GetHeight())
			// Flip the texture
			, ImVec2(-1, 1), ImVec2(0, 0)
		);
		playing_panel.End();
	}
}

void GameLayer::OnGui()
{
}
