#include "EnginePch.h"
#include "Input.h"
#include "Application.h"
#include "Window.h"

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
		return sInstance->mMouse.position;
	}

	Vec2 Input::GetMouseOffset() 
	{
		return sInstance->mMouse.movement;
	}

	void Input::ToggleCursor()
	{
		sInstance->ToggleCursorImplementation();
	}

	void Input::UpdateMouse()
	{
		sInstance->UpdateMouseImplementation();
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
	
	void InputWindows::UpdateMouseImplementation()
	{
		auto window = static_cast<GLFWwindow*>(
			Application::Get().GetWindow().GetOSWindow()
			);
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		mMouse.position = Vec2(x, y);
		mMouse.movement = mMouse.previous - mMouse.position;
		mMouse.previous = mMouse.position;
	}
}