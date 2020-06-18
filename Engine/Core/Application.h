#pragma once

#include "LayerStack.h"

namespace Engine
{
	class Event;
	class Window;
	class CollisionSystem;
	class EngineGUI;
	class FrameBuffer;
	class Scene;

	class Application
	{
	public:
		Application(Ref<Camera3D> camera = nullptr);
		virtual ~Application();

		static Application* Get();

		void Run();
		void OnEvent(Event& event);
		void PushLayer(Layer* layer);
		void PopLayer();
		inline bool IsPlaying() const
		{
			return mPlaying;
		}
		
		Window& GetWindow();
		EngineGUI& GetEngineGUI();
		Scene& GetScene();
		Ref<FrameBuffer> GetBoundFrameBuffer();
	private:
		static Application* sInstance;
		
		// Engine setup to display the application 
		// in engine mode.
		Ref<Camera3D> mEngineCamera;
		Ref<FrameBuffer> mFrameBuffer;

		Scope<Window>		   mWindow;
		Ref<CollisionSystem>   mCollisionSystem;
		Scope<EngineGUI>	   mEngineGUI;
		Scope<Scene>			  mScene;
		bool				   mRunning = true;
		bool				   mPlaying = false;
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
		void RenderPlayPanel();
	protected:
		Ref<Camera3D> mApplicationCamera;
		void OnEngineGUIRender();
	};

	// Has to be define by the game
	Application* CreateApplication();
}