#include "EnginePch.h"
#include "Application.h"
#include "Log.h"
#include "Renderer/Renderer.h"
#include "Util/Matrix.h"

#define bind_function(x) std::bind(&x, this, std::placeholders::_1)

#ifdef ENGINE_WINDOWS
	#define get_engine_time glfwGetTime()
#endif // ENGINE_WINDOWS

namespace Engine
{
	Application* Application::s_instance = nullptr;

	Application::Application()
		: m_layerStack()
	{
		ENGINE_ASSERT(!s_instance, "Application already created");
		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::create());
		m_window->setEventCallback(
			bind_function(Application::onEvent)
		);
	}

	Application::~Application()
	{
	}
	
	void Application::run()
	{
		while (m_running)
		{
			// --- FPS synchronisation ---
			m_deltaTime = get_engine_time - m_time;
			m_time = get_engine_time;
			if (m_deltaTime < m_FPS_CAP)
				Sleep(m_FPS_CAP - m_deltaTime);
			// ---------------------------

			// --- Updates ---
			for (Layer* layer : m_layerStack)
			{
				layer->onUpdate(m_deltaTime);
			}
			// ---------------
			
			m_window->onUpdate(m_deltaTime);
		}
	}
	
	void Application::onEvent(
		Event& event
	)
	{
		if (event.type == Event::Type::Closed || Input::isKeyPressed(GLFW_KEY_ESCAPE))
		{
			m_running = false;
			event.hasBeenHandled();
		}
		
		else if (event.type == Event::Type::Resized)
		{
			m_window->resize(event.sizeEvent.width, event.sizeEvent.height);
			glViewport(0, 0, event.sizeEvent.width, event.sizeEvent.height);
		}
		
		if (!m_layerStack.isEmpty())
		{
			for (auto layer = m_layerStack.end() - 1;
				 (layer != m_layerStack.begin()) &&
				 !event.isHandled();
				 --layer
			)
			{
				(*layer)->onEvent(event);
			}
		}
		
	}	
}