#include "EnginePch.h"
#include "Application.h"
#include "Log.h"

#define bind_function(x) std::bind(&x, this, std::placeholders::_1)
#define FPS_CAP 60.0
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
			glClearColor(0.7f, 1.f, 0.7f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_deltaTime = std::max(get_engine_time - m_time, (1.0 / FPS_CAP));
			m_time = get_engine_time;

			m_window->onUpdate(m_deltaTime);

			for (Layer* layer : m_layerStack)
			{
				layer->onUpdate(m_deltaTime);
			}
		}
	}
	void Application::onEvent(Event& event)
	{
		if (event.type == Event::Type::Closed || Input::isKeyPressed(GLFW_KEY_ESCAPE))
		{
			m_running = false;
			event.hasBeenHandled();
		}
		else if (event.type == Event::Type::Resized)
		{
			m_window->resize(event.sizeEvent.width, event.sizeEvent.height);
			event.hasBeenHandled();
		}
		else
		{
			for (auto layer = m_layerStack.end(); layer != m_layerStack.begin() && !event.isHandled(); --layer)
			{
				(*layer)->onEvent(event);
			}
		}
	}
	void Application::pushLayer(Layer* layer)
	{
		m_layerStack.push(layer);
	}
	void Application::popLayer()
	{
		m_layerStack.pop();
	}
}