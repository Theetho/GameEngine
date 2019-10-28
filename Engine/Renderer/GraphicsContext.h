#pragma once

namespace Engine
{

/// Abstract base class

	class GraphicsContext
	{
	public:
		virtual void initialize() = 0;
		
		virtual void swapBuffers() = 0;
	};

/// OpenGL context

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(
			GLFWwindow* window
		);

		~OpenGLContext();

		void initialize() override;

		void swapBuffers() override;
	private:
		GLFWwindow* m_window;
	};
}