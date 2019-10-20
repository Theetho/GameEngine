#pragma once

#include "Maths/Vec2.h"

namespace Engine
{
	class ENGINE_API Input
	{
	public:
		Input();
		~Input();

		inline static bool isKeyPressed(const int& keycode)
		{
			return s_instance->isKeyPressedImplementation(keycode);
		}
		inline static bool isMouseButtonPressed(const int& button)
		{
			return s_instance->isMouseButtonPressedImplementation(button);
		}
		inline static Vec2d getMousePosition()
		{
			return s_instance->getMousePositionImplementation();
		}

		static Input* create();
	protected:
		virtual bool isKeyPressedImplementation(const int& keycode) const = 0;
		virtual bool isMouseButtonPressedImplementation(const int& button) const = 0;
		virtual Vec2d getMousePositionImplementation() const = 0;
	private:
		static Input* s_instance;
	};

	class InputWindows : public Input
	{
	public:
		InputWindows();
		~InputWindows();

	private:
		virtual bool isKeyPressedImplementation(const int& keycode) const override;
		virtual bool isMouseButtonPressedImplementation(const int& button) const override;
		virtual Vec2d getMousePositionImplementation() const override;

	};
}