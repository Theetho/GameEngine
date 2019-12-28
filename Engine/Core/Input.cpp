#include "EnginePch.h"
#include "Input.h"
#include "Application.h"

namespace Engine
{
	Input* Input::sInstance = nullptr;

	Input::Input()
		: mCursor(true)
	{
		ENGINE_ASSERT(!sInstance, "Input instance already created");
		sInstance = this;
	}

	Input::~Input()
	{}

	Input* Input::Create()
	{
	#ifdef ENGINE_WINDOWS
		return new InputWindows;
	#endif // ENGINE_WINDOWS
	}

	bool Input::IsKeyPressed(int keycode)
	{
		return sInstance->IsKeyPressedImplementation(keycode);
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		return sInstance->IsMouseButtonPressedImplementation(button);
	}

	Vec2 Input::GetMousePosition() 
	{
		return sInstance->GetMousePositionImplementation();
	}

	Vec2 Input::GetMouseOffset() 
	{
		return sInstance->GetMouseOffsetImplementation();
	}

	void Input::ToggleCursor()
	{
		sInstance->ToggleCursorImplementation();
	}

/// Windows input 
	InputWindows::InputWindows()
		: Input()
	{}
	
	InputWindows::~InputWindows()
	{}
	
	bool InputWindows::IsKeyPressedImplementation(int keycode) const
	{
		auto window = static_cast<GLFWwindow*>(
			Application::Get().GetWindow().GetOSWindow()
		);
		int key_state = glfwGetKey(window, keycode);
		
		return key_state == GLFW_PRESS || key_state == GLFW_REPEAT;
	}
	
	bool InputWindows::IsMouseButtonPressedImplementation(int button) const
	{
		auto window = static_cast<GLFWwindow*>(
			Application::Get().GetWindow().GetOSWindow()
		);
		int button_state = glfwGetMouseButton(window, button);

		return button_state == GLFW_PRESS || button_state == GLFW_REPEAT;
	}
	
	Vec2 InputWindows::GetMousePositionImplementation()
	{
		auto window = static_cast<GLFWwindow*>(
			Application::Get().GetWindow().GetOSWindow()
		);
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return Vec2(x, y);
	}
	
	Vec2 InputWindows::GetMouseOffsetImplementation()
	{
		auto window = static_cast<GLFWwindow*>(
			Application::Get().GetWindow().GetOSWindow()
			);
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		Vec2 current_mouse_position(x, y);

		Vec2 offset = mPreviousMousePosition - current_mouse_position;

		mPreviousMousePosition = current_mouse_position;

		return offset;
	}
	
	void InputWindows::ToggleCursorImplementation()
	{
		mCursor = !mCursor;

		auto window = static_cast<GLFWwindow*>(
			Application::Get().GetWindow().GetOSWindow()
		);
		mCursor
		?
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL)
		:
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED) 
		;
	}
}