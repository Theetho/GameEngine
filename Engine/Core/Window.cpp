#include "EnginePch.h"
#include "Window.h"
#include "API/OpenGL/OpenGLContext.h"
#include "Log.h"

namespace Engine
{

/// Window

	bool Window::s_GLFWInitialized(false);

	Window::Window()
	{
	}

	Window::~Window()
	{
	}

	Window* Window::Create(
		const Window::WindowData& windowData
	)
	{
		#ifdef ENGINE_WINDOWS
		return new WindowWindows(windowData);
		#endif // ENGINE_WINDOWS
	}

/// Windows window

	WindowWindows::WindowWindows(
		const WindowData& windowData
	)
	{
		this->initialize(windowData);
	}
	
	WindowWindows::~WindowWindows()
	{
		this->shutdown();
	}
	
	void WindowWindows::onUpdate(
		const double& delta
	)
	{
		glfwPollEvents();
		m_context->swapBuffers();
	}
	
	void WindowWindows::resize(
		const unsigned int& width, 
		const unsigned int& height
	)
	{
		m_data.width =	width;
		m_data.height = height;

		glfwSetWindowSize(m_window, width, height);

		ENGINE_LOG_TRACE("Resized the window {0} to {1} x {2}",
						 m_data.title, width, height);
	}

	void WindowWindows::setFullscreen(const bool& set)
	{
		if (set)
		{
			auto monitor = glfwGetPrimaryMonitor();
			auto videoMode = glfwGetVideoMode(monitor);
			glfwSetWindowMonitor(m_window, monitor, 0, 0, videoMode->width, videoMode->height, GLFW_DONT_CARE);
		}
		else
		{
			glfwSetWindowMonitor(m_window, nullptr, 200, 200, m_data.getDefaultWidth(), m_data.getDefaultHeight(), GLFW_DONT_CARE);
		}
	}
	
	void WindowWindows::initialize(
		const WindowData& windowData
	)
	{
		m_data.width =	windowData.width;
		m_data.height = windowData.height;
		m_data.title =	windowData.title;

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

		m_context = new OpenGLContext(m_window);
		m_context->initialize();

		glfwSetWindowUserPointer(m_window, &m_data);

		this->setCallbacks();

		ENGINE_LOG_TRACE(
			"Creating a window \"{0}\", {1} x {2}",
			m_data.title, m_data.width, m_data.height
		);
	}
	
	void WindowWindows::shutdown()
	{
		glfwDestroyWindow(m_window);
		ENGINE_LOG_TRACE("Closed the window \"{0}\"", m_data.title);
		delete m_context;
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
					event.mouseButtonEvent(button);
				}
				else if (action == GLFW_RELEASE)
				{
					event.type = Event::MouseButtonReleased;
					event.mouseButtonEvent(button);
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
				event.mouseScrolledEvent(xoffset, yoffset);

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