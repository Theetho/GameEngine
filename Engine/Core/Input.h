#pragma once

#include "Include/Maths.h"

namespace Engine
{
	class Input
	{
	public:
		Input();
		~Input();

		static Input* Create();

		static bool IsKeyPressed(int keycode);
		static bool IsMouseButtonPressed(int button);
		static Vec2 GetMousePosition();
		static Vec2 GetMouseOffset();
		static void ToggleCursor();
	protected:
		virtual bool IsKeyPressedImplementation(int keycode) const = 0;
		virtual bool IsMouseButtonPressedImplementation(int button) const = 0;
		virtual Vec2 GetMousePositionImplementation() = 0;
		virtual Vec2 GetMouseOffsetImplementation() = 0;
		virtual void ToggleCursorImplementation() = 0;
	private:
		static Input* sInstance;
	protected:
		bool mCursor;
		Vec2 mPreviousMousePosition;
	};

	class InputWindows : public Input
	{
	public:
		InputWindows();
		~InputWindows();
	private:
		bool IsKeyPressedImplementation(int keycode) const override;
		bool IsMouseButtonPressedImplementation(int button) const override;
		Vec2 GetMousePositionImplementation() override;
		Vec2 GetMouseOffsetImplementation() override;
		void ToggleCursorImplementation() override;
	};
}