#pragma once

#include "Renderer/GraphicsContext.h"

namespace Engine
{
	class OpenGLContext : public GraphicsContext
	{
	public:

		#ifdef ENGINE_WINDOWS
		OpenGLContext(
			GLFWwindow* window
		);
		#endif

		~OpenGLContext();

		void initialize() override;

		void swapBuffers() override;
	private:
		GLFWwindow* m_window;
	};
}