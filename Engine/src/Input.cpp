#include "EnginePch.h"
#include "Input.h"
#include "Application.h"

namespace Engine
{
	Input* Input::s_instance = nullptr;

	Input::Input()
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
	bool InputWindows::isKeyPressedImplementation(const int& keycode) const
	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getOSWindow());
		int key_state = glfwGetKey(window, keycode);
		
		return key_state == GLFW_PRESS || key_state == GLFW_REPEAT;
	}
	bool InputWindows::isMouseButtonPressedImplementation(const int& button) const
	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getOSWindow());
		int button_state = glfwGetMouseButton(window, button);

		return button_state == GLFW_PRESS || button_state == GLFW_REPEAT;
	}
	Vec2d InputWindows::getMousePositionImplementation() const
	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getOSWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return Vec2d(x, y);
	}
}