#pragma once

#include "Input.h"

#define BIT(x) x << 1

#define CreateEngineEvent(x) Event event;\
							 event.mType = x;

// Event class header based on the SFML Event class and the one in The Cherno serie

namespace Engine
{
	class Event
	{
	public:
		struct SizeEvent
		{
			unsigned int width;
			unsigned int height;

			inline void operator()(unsigned int width, unsigned int height)
			{
				this->width  = width;
				this->height = height;
			}
		};			 

		struct TextEvent
		{
			unsigned int text;

			inline void operator()(unsigned int text)
			{
				this->text = text;
			}
		};

		struct KeyboardEvent
		{
			int code;

			inline void operator()(int code)
			{
				this->code = code;
			}
		};
		
		struct MouseScrolledEvent
		{
			double x;
			double y;

			inline void operator()(double x, double y)
			{
				this->x = x;
				this->y = y;
			}
		};

		struct MouseMovedEvent
		{
			double x;
			double y;

			inline void operator()(double x, double y)
			{
				this->x = x;
				this->y = y;
			}
		};

		struct MouseButtonEvent
		{
			int button;

			inline void operator()(int button)
			{
				this->button = button;
			}
		};

		enum Type
		{
			None,
			Resized,
			Closed,
			TextEntered,
			KeyPressed,
			KeyReleased,
			MouseScrolled,
			MouseMoved,
			MouseButtonPressed,
			MouseButtonReleased,
		};

		Type mType;
		union
		{
			SizeEvent			mSizeEvent;
			TextEvent			mTextEvent;
			KeyboardEvent		mKeyEvent;
			MouseScrolledEvent	mMouseScrolledEvent;
			MouseMovedEvent		mMouseMovedEvent;
			MouseButtonEvent	mMouseButtonEvent;
		};

		std::string ToString();
		bool IsHandled() const;
		void SetIsHandled(bool handled);
	private:
		bool mHandled = false;
	};

}
