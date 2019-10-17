#include "EnginePch.h"
#include "Window.h"
#include "ConfigFile.h"

namespace Engine
{

/// Window

	bool Window::s_GLFWInitialized(false);

	Window::~Window()
	{
	}
	Window* Window::create(const Window::WindowData& windowData)
	{
		return new WindowWindows(windowData);
	}

/// Window's implementation on Windows

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
	void WindowWindows::resize(const unsigned int& width, const unsigned int& height)
	{
		m_data.width =	width;
		m_data.height = height;

		glfwSetWindowSize(m_window, width, height);

		ENGINE_LOG_INFO("Resized the window {0} to {1} x {2}",
						 m_data.title, width, height);
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
			int status = glfwInit();
			ENGINE_ASSERT(status, "Failed to initialize GLFW");
			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow(
			m_data.width,
			m_data.height,
			m_data.title.c_str(),
			nullptr, nullptr
		);

		glfwMakeContextCurrent(m_window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ENGINE_ASSERT(status, "Failed to initialize GLAD");

		glfwSetWindowUserPointer(m_window, &m_data);

		this->setCallbacks();
	}
	void WindowWindows::shutdown()
	{
		glfwDestroyWindow(m_window);
		ENGINE_LOG_INFO("Closed the window \"{0}\"", m_data.title);
	}
	void WindowWindows::setCallbacks()
	{
		// Resize window
		glfwSetWindowSizeCallback(m_window, [](
			GLFWwindow* window,
			int width,
			int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;

				create_event(Event::Resized);
				event.sizeEvent(width, height);

				data.eventCallback(event);
			}
		);

		// Closing the window
		glfwSetWindowCloseCallback(m_window, [](
			GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				create_event(Event::Closed);
				
				data.eventCallback(event);
			}
		);

		// Keyboard events
		glfwSetKeyCallback(m_window, [](
			GLFWwindow* window,
			int key,
			int scancode,
			int action,
			int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				Event event;

				if (action == GLFW_PRESS)
				{
					event.type = Event::KeyPressed;
					event.keyEvent(key);
				}
				else if (action == GLFW_RELEASE)
				{
					event.type = Event::KeyReleased;
					event.keyEvent(key);
				}
				
				data.eventCallback(event);
			}
		);

		glfwSetMouseButtonCallback(m_window, [](
			GLFWwindow* window,
			int button,
			int action,
			int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				Event event;

				if (action == GLFW_PRESS)
				{
					event.type = Event::MouseButtonPressed;
					event.keyEvent(button);
				}
				else if (action == GLFW_RELEASE)
				{
					event.type = Event::MouseButtonReleased;
					event.keyEvent(button);
				}

				data.eventCallback(event);
			}
		);

		// Text entered
		glfwSetCharCallback(m_window, [](
			GLFWwindow* window,
			unsigned int codepoint)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				create_event(Event::TextEntered);
				event.textEvent(codepoint);

				data.eventCallback(event);
			}
		);

		// Scrolled event (only on y-axis)
		glfwSetScrollCallback(m_window, [](
			GLFWwindow* window,
			double xoffset, 
			double yoffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				create_event(Event::MouseScrolled);
				event.mouseScrolledEvent(yoffset);

				data.eventCallback(event);
			}
		);

		glfwSetCursorPosCallback(m_window, [](
			GLFWwindow* window,
			double xpos,
			double ypos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				create_event(Event::MouseMoved);
				event.mouseMovedEvent(xpos, ypos);

				data.eventCallback(event);
			}
		);
	}
};