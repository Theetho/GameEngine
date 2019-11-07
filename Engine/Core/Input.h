#pragma once

#include "Maths.h"

namespace Engine
{
	class Input
	{
	public:
		Input();

		~Input();

		inline static bool isKeyPressed(
			const int& keycode
		)
		{
			return s_instance->isKeyPressedImplementation(keycode);
		}

		inline static bool isMouseButtonPressed(
			const int& button
		)
		{
			return s_instance->isMouseButtonPressedImplementation(button);
		}

		inline static Vec2 getMousePosition()
		{
			return s_instance->getMousePositionImplementation();
		}

		inline static Vec2 getMouseOffset()
		{
			return s_instance->getMouseOffsetImplementation();
		}

		inline static void toggleCursor()
		{
			s_instance->toggleCursorImplementation();
		}

		static Input* Create();
	protected:
		virtual bool isKeyPressedImplementation(
			const int& keycode
		) const = 0;

		virtual bool isMouseButtonPressedImplementation(
			const int& button
		) const = 0;

		virtual Vec2 getMousePositionImplementation() const = 0;
		
		virtual Vec2 getMouseOffsetImplementation() = 0;

		virtual void toggleCursorImplementation() = 0;
	private:
		static Input* s_instance;
	protected:
		bool m_cursor;
		Vec2 m_previousMousePosition;
	};

	class InputWindows : public Input
	{
	public:
		InputWindows();
		~InputWindows();

	private:
		virtual bool isKeyPressedImplementation(
			const int& keycode
		) const override;

		virtual bool isMouseButtonPressedImplementation(
			const int& button
		) const override;

		virtual Vec2 getMousePositionImplementation() const override;

		virtual Vec2 getMouseOffsetImplementation() override;
	
		virtual void toggleCursorImplementation() override;
	};
}