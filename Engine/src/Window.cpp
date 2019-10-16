#include "EnginePch.h"
#include "Window.h"
#include "ConfigFile.h"


namespace Engine
{
	bool Window::s_GLFWInitialized(false);

	Window::~Window()
	{
	}
	Window* Window::create(const Window::WindowData& windowData)
	{
		return new WindowWindows(windowData);
	}


	WindowWindows::WindowWindows(const WindowData& windowData)
	{
		this->initialize(windowData);
	}
	WindowWindows::~WindowWindows()
	{
		this->shutdown();
	}
	void WindowWindows::onUpdate(const double& delta)
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}
	void WindowWindows::initialize(const WindowData& windowData)
	{
		m_data.width =	windowData.width;
		m_data.height = windowData.height;
		m_data.title =	windowData.title;

		ENGINE_LOG_INFO(
			"Creating a window \"{0}\", {1} x {2}",
			m_data.title, m_data.width, m_data.height
		);

		if (!s_GLFWInitialized)
		{
			glfwInit();
			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow(
			m_data.width,
			m_data.height,
			m_data.title.c_str(),
			nullptr, nullptr
		);

		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
	}
	void WindowWindows::shutdown()
	{
		glfwDestroyWindow(m_window);
	}
};