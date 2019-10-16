#pragma once

#include "Export.h"
#include "Window.h"

namespace Engine
{
	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void run();
	private:
		std::unique_ptr<Window> m_window;
		bool					m_running = true;
	};

	// Has to be define by the game
	Application* createApplication();
}