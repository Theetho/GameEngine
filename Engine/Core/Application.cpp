#include "EnginePch.h"
#include "Application.h"
#include <thread>
#include <chrono>
#include "Include/Core.h"
#include "System/CollisionSystem.h"
#include "Renderer/Rendering/Renderer.h"

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
		mCollisionSystem = CollisionSystem::Get();
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
			
			mCollisionSystem->OnUpdate(mTimeManager.mDeltaTime);
			
			mWindow->OnUpdate(mTimeManager.mDeltaTime);

			mTimeManager.mDeltaTime = GetEngineTime - mTimeManager.mTime;
			
			this->ManageTime();
			// ---------------------------
		}
	}
	
	void Application::OnEvent(Event& event)
	{
		if (event.mType == Event::Type::Closed || Input::IsKeyPressed(GLFW_KEY_ESCAPE))
		{
			mRunning = false;
			event.SetIsHandled(true);
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
}