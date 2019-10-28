#include "EnginePch.h"
#include "GraphicsContext.h"
#include "Core/Log.h"

namespace Engine
{
/// OpenGL context

	OpenGLContext::OpenGLContext(
		GLFWwindow* window
	)
		: m_window(window)
	{
		ENGINE_ASSERT(m_window, "Window is nullptr");
	}

	OpenGLContext::~OpenGLContext()
	{}

	void OpenGLContext::initialize()
	{
		glfwMakeContextCurrent(m_window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ENGINE_ASSERT(status, "Failed to initialize GLAD");

		ENGINE_LOG_INFO("OpenGL info :");
		ENGINE_LOG_INFO("  -> Vendor   : {0}", glGetString(GL_VENDOR));
		ENGINE_LOG_INFO("  -> Renderer : {0}", glGetString(GL_RENDERER));
		ENGINE_LOG_INFO("  -> Version  : {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(m_window);
	}
}