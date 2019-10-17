#include "EnginePch.h"
#include "Application.h"

#define bind_function(x) std::bind(&x, this, std::placeholders::_1)

namespace Engine
{
	Application::Application()
		: m_layerStack()
	{
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
			m_window->onUpdate(0.0);

			for (Layer* layer : m_layerStack)
			{
				layer->onUpdate(0.0);
			}
		}
	}
	void Application::onEvent(Event& event)
	{
		if		(event.type == Event::Type::Closed)
			m_running = false;
		else if (event.type == Event::Type::Resized)
			m_window->resize(event.sizeEvent.width, event.sizeEvent.height);
		else
			for (auto layer = m_layerStack.end(); layer != m_layerStack.begin(); --layer)
			{
				(*layer)->onEvent(event);
				if (event.isHandled())
					break;
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