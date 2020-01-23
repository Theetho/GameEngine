#pragma once

#include "LayerStack.h"

namespace Engine
{
	class Event;
	class Layer;
	class Window;
	class CollisionSystem;

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
		struct TimeManager
		{
			double mTime = 0.0;
			double mDeltaTime = 0.03;
			double mTimeSpent = 0.0;
			unsigned int mFrames = 0;
		};
		TimeManager			   mTimeManager;
		double				   mFpsCap = 1.0 / 60.0;

		void ManageTime();
	};

	// Has to be define by the game
	Application* CreateApplication();
}