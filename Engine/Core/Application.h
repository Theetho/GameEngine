#pragma once

#include "Window.h"
#include "LayerStack.h"
#include "Input.h"
#include "Camera3D.h"
#include "Include/Renderer.h"
#include "System/CollisionSystem.h"

namespace Engine
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		static Application& Get();

		void Run();
		void OnEvent(Event& event);
		void PushLayer(Layer* layer);
		void PopLayer();
		
		Window& GetWindow();
	private:
		static Application*	   sInstance;
		
		Scope<Window>		   mWindow;
		Ref<CollisionSystem>   mCollisionSystem;
		bool				   mRunning = true;
		LayerStack			   mLayerStack;
		double				   mTime = 0.0, mDeltaTime = 0.0;
		double				   mFpsCap = 1.0 / 60.0;
	};

	// Has to be define by the game
	Application* CreateApplication();
}