#include "EnginePch.h"
#include "Application.h"
#include "Log.h"
#include "Renderer/Rendering/Renderer.h"
#include "Util/Matrix.h"
#include <thread>
#include <chrono>

#define bind_function(x) std::bind(&x, this, std::placeholders::_1)

#ifdef ENGINE_WINDOWS
	#define get_engine_time glfwGetTime()
#endif // ENGINE_WINDOWS

namespace Engine
{
	Application* Application::s_instance = nullptr;

	Application::Application()
		: m_layerStack()
		, m_time(get_engine_time)
	{
		ENGINE_ASSERT(!s_instance, "Application already created");
		s_instance = this;

		m_window = Scope<Window>(Window::Create());
		m_window->setEventCallback(
			bind_function(Application::onEvent)
		);

		m_collisionSystem = CollisionSystem::Get();
	}

	Application::~Application()
	{
	}
	
	void Application::run()
	{
		while (m_running)
		{
			m_time = get_engine_time;

			// --- Updates ---
			for (Layer* layer : m_layerStack)
			{
				layer->onUpdate(m_deltaTime);
			}
			// ---------------
			
			m_collisionSystem->onUpdate(m_deltaTime);

			m_window->onUpdate(m_deltaTime);

			m_deltaTime = get_engine_time - m_time;
			
			// ---------------------------
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
			Renderer::setViewport(event.sizeEvent.width, event.sizeEvent.height);
		}
		
		if (!m_layerStack.isEmpty())
		{
			auto layer = m_layerStack.end();
			while (layer != m_layerStack.begin() && !event.isHandled())
			{
				(*--layer)->onEvent(event);
			}
		}
		
	}	
}