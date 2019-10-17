#pragma once

#include "Export.h"
#include "Window.h"
#include "LayerStack.h"

namespace Engine
{
	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void run();
		void onEvent(Event& event);
		void pushLayer(Layer* layer);
		void popLayer();
	private:
		std::unique_ptr<Window> m_window;
		bool					m_running = true;
		LayerStack				m_layerStack;
	};

	// Has to be define by the game
	Application* createApplication();
}