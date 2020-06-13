#include "EnginePch.h"
#include "Application.h"
#include <thread>
#include <chrono>
#include "Include/Core.h"
#include "Renderer/Rendering/Renderer.h"
#include "GUI/GUI.h"
#include "GUI/EngineGUI.h"

#define BindFunction(x) std::bind(&x, this, std::placeholders::_1)

#ifdef ENGINE_WINDOWS
	#define GetEngineTime glfwGetTime()
#endif // ENGINE_WINDOWS

namespace Engine
{
	Application* Application::sInstance = nullptr;

	Application::Application()
		: mLayerStack()
	{
		mTimeManager.mTime = GetEngineTime;

		ENGINE_ASSERT(!sInstance, "Application already created");
		sInstance = this;

		mWindow = Scope<Window>(Window::Create());
		mWindow->SetEventCallback(BindFunction(Application::OnEvent));

		mEngineGUI = CreateScope<EngineGUI>();
		GUI::Begin();
		mEngineGUI->Initialize();
		GUI::End();
	}

	Application::~Application()
	{}

	Application& Application::Get()
	{
		return *sInstance;
	}
	
	void Application::Run()
	{
		Input::UpdateMouse();
		while (mRunning)
		{
			mTimeManager.mTime = GetEngineTime;

			Input::UpdateMouse();
	
			// --- Updates ---
			for (Layer* layer : mLayerStack)
			{
				layer->OnUpdate(mTimeManager.mDeltaTime);
			}
			// ---------------

			if (!mPlaying)
			{
				GUI::Begin();
				mEngineGUI->Render();
				for (Layer* layer : mLayerStack)
				{
					layer->OnEngineGui();
				}
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
				event.SetIsHandled(true);
			}
		}


		else if (event.mType == Event::Type::Resized)
		{
			mWindow->Resize(event.mSizeEvent.width, event.mSizeEvent.height);
			Renderer::SetViewport(event.mSizeEvent.width, event.mSizeEvent.height);
		}
		
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