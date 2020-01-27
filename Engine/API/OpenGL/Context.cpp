#include "EnginePch.h"
#include "Context.h"

namespace Engine
{
	namespace OpenGL
	{
		#ifdef ENGINE_WINDOWS
		Context::Context(GLFWwindow* window)
			: mWindow(window)
		{
			ENGINE_ASSERT(mWindow, "Window is nullptr");
		}
		#endif

		Context::~Context()
		{
		}

		void Context::Initialize()
		{
			#ifdef ENGINE_WINDOWS	
			glfwMakeContextCurrent(mWindow);
			int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			ENGINE_ASSERT(status, "Failed to initialize GLAD");
			#endif

			ENGINE_LOG_INFO(" info :");
			ENGINE_LOG_INFO("  -> Vendor   : {0}", glGetString(GL_VENDOR));
			ENGINE_LOG_INFO("  -> Renderer : {0}", glGetString(GL_RENDERER));
			ENGINE_LOG_INFO("  -> Version  : {0}", glGetString(GL_VERSION));

			glEnable(GL_DEPTH_TEST);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}

		void Context::SwapBuffers()
		{
			#ifdef ENGINE_WINDOWS
			glfwSwapBuffers(mWindow);
			#endif
		}
	}
}