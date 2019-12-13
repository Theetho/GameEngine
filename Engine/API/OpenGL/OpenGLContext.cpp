#include "EnginePch.h"
#include "OpenGLContext.h"
#include "Core/Log.h"

namespace Engine
{
	#ifdef ENGINE_WINDOWS
	OpenGLContext::OpenGLContext(
		GLFWwindow* window
	)
		: m_window(window)
	{
		ENGINE_ASSERT(m_window, "Window is nullptr");
	}
	#endif

	OpenGLContext::~OpenGLContext()
	{}

	void OpenGLContext::initialize()
	{
		#ifdef ENGINE_WINDOWS
		
		glfwMakeContextCurrent(m_window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ENGINE_ASSERT(status, "Failed to initialize GLAD");
		
		#endif

		ENGINE_LOG_INFO("OpenGL info :");
		ENGINE_LOG_INFO("  -> Vendor   : {0}", glGetString(GL_VENDOR));
		ENGINE_LOG_INFO("  -> Renderer : {0}", glGetString(GL_RENDERER));
		ENGINE_LOG_INFO("  -> Version  : {0}", glGetString(GL_VERSION));
		
		glEnable(GL_DEPTH_TEST);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}

	void OpenGLContext::swapBuffers()
	{
		#ifdef ENGINE_WINDOWS
		glfwSwapBuffers(m_window);
		#endif
	}
}