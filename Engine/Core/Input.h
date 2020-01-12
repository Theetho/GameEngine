#pragma once

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
		virtual void ToggleCursorImplementation() = 0;
		virtual void UpdateMouseImplementation() = 0;
	private:
		friend class Application;
		static Input* sInstance;
		static void UpdateMouse();
	protected:
		bool mCursor;
		struct Mouse
		{
			Vec2 position;
			Vec2 previous;
			Vec2 movement;
		};
		Mouse mMouse;
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
		void ToggleCursorImplementation() override;
		void UpdateMouseImplementation() override;
	};
}