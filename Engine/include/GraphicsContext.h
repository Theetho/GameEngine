#pragma once

#include "Export.h"


namespace Engine
{
	class GraphicsContext
	{
	public:
		virtual void initialize() = 0;
		virtual void swapBuffers() = 0;

	private:

	};

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window);
		~OpenGLContext();

		void initialize() override;
		void swapBuffers() override;

	private:
		GLFWwindow* m_window;
	};
}