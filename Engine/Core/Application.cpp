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
		, mTime(GetEngineTime)
	{
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
		while (mRunning)
		{
			mTime = GetEngineTime;

			Input::UpdateMouse();

			mCollisionSystem->OnUpdate(mDeltaTime);
			
			// --- Updates ---
			for (Layer* layer : mLayerStack)
			{
				layer->OnUpdate(mDeltaTime);
			}
			// ---------------
			
			mWindow->OnUpdate(mDeltaTime);

			mDeltaTime = GetEngineTime - mTime;
			
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
}