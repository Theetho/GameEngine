#include "EnginePch.h"
#include "Input.h"
#include "Application.h"

namespace Engine
{
	Input* Input::s_instance = nullptr;

	Input::Input()
		: m_cursor(true)
		, m_previousMousePosition()
	{
		ENGINE_ASSERT(!s_instance, "Input instance already created");
		s_instance = this;
	}

	Input::~Input()
	{
	}

	Input* Input::create()
	{
#ifdef ENGINE_WINDOWS
		return new InputWindows;
#endif // ENGINE_WINDOWS
	}


/// Windows input 
	InputWindows::InputWindows()
		: Input()
	{
	}
	
	InputWindows::~InputWindows()
	{
	}
	
	bool InputWindows::isKeyPressedImplementation(
		const int& keycode
	) const
	{
		auto window = static_cast<GLFWwindow*>(
			Application::get().getWindow().getOSWindow()
		);
		int key_state = glfwGetKey(window, keycode);
		
		return key_state == GLFW_PRESS || key_state == GLFW_REPEAT;
	}
	
	bool InputWindows::isMouseButtonPressedImplementation(
		const int& button
	) const
	{
		auto window = static_cast<GLFWwindow*>(
			Application::get().getWindow().getOSWindow()
		);
		int button_state = glfwGetMouseButton(window, button);

		return button_state == GLFW_PRESS || button_state == GLFW_REPEAT;
	}
	
	Vec2 InputWindows::getMousePositionImplementation() const
	{
		auto window = static_cast<GLFWwindow*>(
			Application::get().getWindow().getOSWindow()
		);
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return Vec2(x, y);
	}
	
	Vec2 InputWindows::getMouseOffsetImplementation()
	{
		auto window = static_cast<GLFWwindow*>(
			Application::get().getWindow().getOSWindow()
			);
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		Vec2 currentMousePosition(x, y);

		Vec2 offset = 
			m_previousMousePosition 
		  - currentMousePosition
		;

		m_previousMousePosition = currentMousePosition;

		return offset;
	}
	
	void InputWindows::toggleCursorImplementation()
	{
		m_cursor = !m_cursor;

		auto window = static_cast<GLFWwindow*>(
			Application::get().getWindow().getOSWindow()
		);
		m_cursor
		?
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL)
		:
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED) 
		;
	}
}