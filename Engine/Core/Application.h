#pragma once

#include "Window.h"
#include "LayerStack.h"
#include "Input.h"
#include "Camera3D.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

namespace Engine
{
	class Application
	{
	public:
		Application();

		virtual ~Application();

		inline static Application& get()
		{ 
			return *s_instance;
		}

		void run();

		void onEvent(
			Event& event
		);
	
		inline void pushLayer(
			Layer* layer
		)
		{
			m_layerStack.push(layer);
		}

		inline void popLayer()
		{
			m_layerStack.pop();
		}

		inline Window& getWindow() 
		{
			return *m_window; 
		}

	private:
		Scope<Window> m_window;
		bool		  m_running = true;
		LayerStack	  m_layerStack;
		double		  m_time = 0.0, m_deltaTime = 0.0;
		double		  m_FPS_CAP = 1.0 / 60.0;
	private:
		static Application* s_instance;
	};

	// Has to be define by the game
	Application* createApplication();
}