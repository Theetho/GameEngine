#include "EnginePch.h"
#include "Window.h"
#include "Log.h"
#define EVENT_CPP
#include "Event.h"
#undef EVENT_CPP
#include "API/OpenGL/Context.h"
#include "GUI/GUI.h"

namespace Engine
{

/// Window

	bool WindowWindows::sGLFWInitialized(false);

	Window::Window()
	{}

	Window::~Window()
	{}

	Window* Window::Create(const WindowData& window_data)
	{
	#ifdef ENGINE_WINDOWS
		return new WindowWindows(window_data);
	#endif // ENGINE_WINDOWS
	}

	unsigned int Window::GetWidth() const
	{
		return mData.width;
	}

	unsigned int Window::GetHeight() const
	{
		return mData.height;
	}

	const std::string& Window::GetTitle() const
	{
		return mData.title;
	}

	void Window::SetEventCallback(const EventCallbackFunction& event_callback)
	{
		mData.event_callback = event_callback;
	}

/// Windows window

	WindowWindows::WindowWindows(const WindowData& window_data)
	{
		this->Initialize(window_data);
	}
	
	WindowWindows::~WindowWindows()
	{
		this->Shutdown();
	}
	
	void WindowWindows::OnUpdate(const double& delta)
	{
		glfwPollEvents();
		mContext->SwapBuffers();
	}
	
	void WindowWindows::Resize(unsigned int width, unsigned int height)
	{
		mData.width =	width;
		mData.height = height;

		glfwSetWindowSize(mWindow, width, height);

		ENGINE_LOG_TRACE("Resized the window {0} to {1} x {2}",
						 mData.title, width, height);
	}

	void* WindowWindows::GetOSWindow()
	{
		return mWindow;
	}

	void WindowWindows::SetFullscreen(bool Set)
	{
		if (Set)
		{
			auto monitor = glfwGetPrimaryMonitor();
			auto videoMode = glfwGetVideoMode(monitor);
			glfwSetWindowMonitor(mWindow, monitor, 0, 0, videoMode->width, videoMode->height, GLFW_DONT_CARE);
		}
		else
		{
			glfwSetWindowMonitor(mWindow, nullptr, 200, 200, mData.GetDefaultWidth(), mData.GetDefaultHeight(), GLFW_DONT_CARE);
		}
	}

	void WindowWindows::SetSize(const Vec2& size)
	{
		glfwSetWindowSize(mWindow, size.x, size.y);
	}

	void WindowWindows::Maximise()
	{
		glfwMaximizeWindow(mWindow);
	}
	
	void WindowWindows::Initialize(const WindowData& window_data)
	{
		mData.width  = window_data.width;
		mData.height = window_data.height;
		mData.title  = window_data.title;

		if (!sGLFWInitialized)
		{
			int status = glfwInit();
			ENGINE_ASSERT(status, "Failed to Initialize GLFW");
			sGLFWInitialized = true;
		}

		mWindow = glfwCreateWindow(mData.width, mData.height, mData.title.c_str(), nullptr, nullptr);

		mContext = new OpenGL::Context(mWindow);
		mContext->Initialize();

		glfwSetWindowUserPointer(mWindow, &mData);

		this->SetCallbacks();

		ENGINE_LOG_TRACE(
			"Creating a window \"{0}\", {1} x {2}",
			mData.title, mData.width, mData.height
		);

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); 
		io.Fonts->AddFontFromFileTTF("../Engine/Assets/Fonts/consola.ttf", 16.0f);
		//ImGui::StyleColorsDark();
		GUI::InitializeStyle();
		ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
		
		auto version = mContext->GetAPIVersion();
		std::stringstream glsl_version;
		glsl_version << "#version " << unsigned char(version[0]) << unsigned char(version[2]) << unsigned char(version[4]);
		ImGui_ImplOpenGL3_Init(glsl_version.str().c_str());
	}
	
	void WindowWindows::Shutdown()
	{
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		glfwDestroyWindow(mWindow);
		ENGINE_LOG_TRACE("Closed the window \"{0}\"", mData.title);
		delete mContext;
		glfwTerminate();
	}
	
	void WindowWindows::SetCallbacks()
	{
		// Resize window
		glfwSetWindowSizeCallback(mWindow, [](
			GLFWwindow* window,
			int width,
			int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;

				CreateEngineEvent(Event::Resized);
				event.mSizeEvent(width, height);

				data.event_callback(event);
			}
		);

		// Closing the window
		glfwSetWindowCloseCallback(mWindow, [](
			GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				CreateEngineEvent(Event::Closed);
				
				data.event_callback(event);
			}
		);

		// Keyboard events
		glfwSetKeyCallback(mWindow, [](
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
					event.mType = Event::KeyPressed;
					event.mKeyEvent(key);
				}
				else if (action == GLFW_RELEASE)
				{
					event.mType = Event::KeyReleased;
					event.mKeyEvent(key);
				}
				
				data.event_callback(event);
			}
		);

		glfwSetMouseButtonCallback(mWindow, [](
			GLFWwindow* window,
			int button,
			int action,
			int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				Event event;

				if (action == GLFW_PRESS)
				{
					event.mType = Event::MouseButtonPressed;
					event.mMouseButtonEvent(button);
				}
				else if (action == GLFW_RELEASE)
				{
					event.mType = Event::MouseButtonReleased;
					event.mMouseButtonEvent(button);
				}

				data.event_callback(event);
			}
		);

		// Text entered
		glfwSetCharCallback(mWindow, [](
			GLFWwindow* window,
			unsigned int codepoint)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				CreateEngineEvent(Event::TextEntered);
				event.mTextEvent(codepoint);

				data.event_callback(event);
			}
		);

		// Scrolled event (only on y-axis)
		glfwSetScrollCallback(mWindow, [](
			GLFWwindow* window,
			double xoffSet, 
			double yoffSet)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				CreateEngineEvent(Event::MouseScrolled);
				event.mMouseScrolledEvent(xoffSet, yoffSet);

				data.event_callback(event);
			}
		);

		glfwSetCursorPosCallback(mWindow, [](
			GLFWwindow* window,
			double xpos,
			double ypos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				CreateEngineEvent(Event::MouseMoved);
				event.mMouseMovedEvent(xpos, ypos);

				data.event_callback(event);
			}
		);
	}
};