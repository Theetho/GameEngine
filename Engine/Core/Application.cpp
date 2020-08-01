#include "EnginePch.h"
#include "Application.h"
#include <thread>
#include <chrono>
#include "Include/Core.h"
#include "Renderer/Rendering/Renderer.h"
#include "GUI/GUI.h"
#include "GUI/EngineGUI.h"
#include "Renderer/Buffer/FrameBuffer.h"

#define BindFunction(x) std::bind(&x, this, std::placeholders::_1)

#ifdef ENGINE_WINDOWS
	#define GetEngineTime glfwGetTime()
#endif // ENGINE_WINDOWS

namespace Engine
{
	Application* Application::sInstance = nullptr;

	Application::Application(Ref<Camera3D> camera)
		: mLayerStack()
		, mApplicationCamera(camera)
		, mEngineCamera(CreateRef<ArcBallCamera>())
		, mScene(CreateRef<Scene>())
	{
		auto cameras_position = Vec3(0, 40, 0);

		if (mApplicationCamera == nullptr) mApplicationCamera = CreateRef<Camera3D>(cameras_position);
		mScene->Clear();
		mScene->AddObject(mApplicationCamera);

		mTimeManager.mTime = GetEngineTime;

		ENGINE_ASSERT(!sInstance, "Application already created");
		sInstance = this;

		mWindow = Scope<Window>(Window::Create());
		mWindow->SetEventCallback(BindFunction(Application::OnEvent));

		mEngineGUI = CreateScope<EngineGUI>();
		GUI::Begin();
		mEngineGUI->Initialize();
		GUI::End();

		auto& playing_panel = mEngineGUI->GetPanel("Playing");
		mFrameBuffer = FrameBuffer::Create(playing_panel.GetSize().x, playing_panel.GetSize().x / mEngineCamera->GetAspectRatio());
		mFrameBuffer->CreateTextureAttachment();
		mFrameBuffer->CreateRenderBuffer();
	}

	Application::~Application()
	{}

	Application* Application::Get()
	{
		return sInstance;
	}
	
	void Application::Run()
	{
		Input::UpdateMouse();
		while (mRunning)
		{
			mTimeManager.mTime = GetEngineTime;

			Input::UpdateMouse();

			// --- Updates ---
			mScene->UpdateLights();
			if (!mPlaying) mFrameBuffer->Bind();
			for (Layer* layer : mLayerStack)
			{
				mPlaying 
				? 
				layer->OnUpdate(mApplicationCamera, mTimeManager.mDeltaTime) 
				: 
				layer->OnUpdate(mEngineCamera, mTimeManager.mDeltaTime)
				;
			}
			if (!mPlaying) mFrameBuffer->Unbind();
			// ---------------

			// Render the engine UI
			if (!mPlaying)
			{
				GUI::Begin();
				mEngineGUI->Render();
				mScene->OnUiRender();
				for (Layer* layer : mLayerStack)
				{
					layer->OnEngineGui();
				}
				RenderPlayPanel();
				GUI::End();
			}

			mWindow->OnUpdate(mTimeManager.mDeltaTime);

			mTimeManager.mDeltaTime = GetEngineTime - mTimeManager.mTime;
			
			this->ManageTime();
			// ---------------------------
		}
	}
	
	void Application::OnEvent(Event& event)
	{
		if (event.mType == Event::Type::Closed)
		{
			mRunning = false;
			event.SetIsHandled(true);
		}

		else if (event.mType == Event::Type::KeyPressed)
		{
			if (event.mKeyEvent.code == ENGINE_KEY_ESCAPE)
			{
				mRunning = false;
				event.SetIsHandled(true);
			}
			else if (event.mKeyEvent.code == ENGINE_KEY_F1)
			{
				mPlaying = !mPlaying;
				Input::ToggleCursor();
				if (mPlaying) mApplicationCamera->UpdateViewMatrix();
				event.SetIsHandled(true);
			}
		}


		else if (event.mType == Event::Type::Resized)
		{
			mWindow->Resize(event.mSizeEvent.width, event.mSizeEvent.height);
			Renderer::SetViewport(event.mSizeEvent.width, event.mSizeEvent.height);
		}
		
		// Update cameras
		mPlaying
		?
		mApplicationCamera->OnEvent(event)
		:
		mEngineCamera->OnEvent(event)
		;

		if (!mLayerStack.IsEmpty())
		{
			auto layer = mLayerStack.end();
			while (layer != mLayerStack.begin() && !event.IsHandled())
			{
				(*--layer)->OnEvent(event);
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		mLayerStack.Push(layer);
	}
	
	void Application::PopLayer()
	{
		mLayerStack.Pop();
	}
	
	Window& Application::GetWindow()
	{
		return *mWindow;
	}

	EngineGUI& Application::GetEngineGUI()
	{
		return *mEngineGUI;
	}

	Ref<Scene> Application::GetScene()
	{
		return mScene;
	}

	Ref<FrameBuffer> Application::GetBoundFrameBuffer()
	{
		return mPlaying ? nullptr : mFrameBuffer;
	}

	void Application::ManageTime()
	{
		mTimeManager.mTimeSpent += mTimeManager.mDeltaTime;
		++mTimeManager.mFrames;

		if (mTimeManager.mTimeSpent >= 1.0)
		{
			ENGINE_LOG_INFO("Average time for frames : {0} ms / Average fps : {1} ", (mTimeManager.mTimeSpent / (double)mTimeManager.mFrames) * 1000.0, mTimeManager.mFrames);
			mTimeManager.mTimeSpent -= 1.0;
			mTimeManager.mFrames = 0.0;
		}
	}

	void Application::RenderPlayPanel()
	{
		auto playing_panel = mEngineGUI->GetPanel("Playing");
		auto scene_texture = mFrameBuffer->GetTextureAttachment();

		playing_panel.Begin();
		ImGui::Image((void*)(intptr_t)scene_texture->GetId()
			, ImVec2(scene_texture->GetWidth(), scene_texture->GetHeight())
			// Flip the texture
			, ImVec2(-1, 1), ImVec2(0, 0)
		);

		ImGui::Text(R"(- Controls:
	* F1 to toggle engine/game mode.
	* In engine mode:
		- LSHIFT + middle mouse to translate the view.
		- Middle mouse to rotate the view.
		- Mouse wheel to zoom in/out.
	* In game mode.
		- Move the mouse to rotate the view.)");
		playing_panel.End();
	}

	void Application::OnEngineGUIRender()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowRounding = 0;

		auto panel_flags =
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoBringToFrontOnFocus;
		float main_menu_height = 0.f;
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Example"))
			{
				ImGui::EndMenu();
			}
			main_menu_height = ImGui::GetWindowHeight();
			ImGui::EndMainMenuBar();
		}

		float panel_height = (float)mWindow->GetHeight() * 0.90f - main_menu_height;

		// Left panel
		ImGui::Begin("Engine-Left-Panel", nullptr, panel_flags);
		ImGui::SetWindowPos({ 0.f, main_menu_height });
		ImGui::SetWindowSize({ mWindow->GetWidth() * 0.15f, panel_height });
		ImGui::End();

		// Playing panel
		ImGui::Begin("Engine-Playing-Panel", nullptr, panel_flags | ImGuiWindowFlags_NoBackground);
		ImGui::SetWindowPos({ mWindow->GetWidth() * 0.15f, main_menu_height });
		ImGui::SetWindowSize({ mWindow->GetWidth() * 0.70f, panel_height });
		ImGui::End();

		// Right panel
		ImGui::Begin("Engine-Right-Panel", nullptr, panel_flags);
		ImGui::SetWindowPos({ mWindow->GetWidth() * 0.85f, main_menu_height });
		ImGui::SetWindowSize({ mWindow->GetWidth() * 0.15f, panel_height });
		ImGui::End();

		// Bottom panel
		ImGui::Begin("Engine-Bottom-Panel", nullptr, panel_flags);
		ImGui::SetWindowPos({ 0.f, main_menu_height + panel_height });
		ImGui::SetWindowSize({ (float)mWindow->GetWidth(), mWindow->GetHeight() - (main_menu_height + panel_height) });
		ImGui::End();

		style.WindowRounding = 7;
	}
}