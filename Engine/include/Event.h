#pragma once

#include "Export.h"

#define BIT(x) x << 1

#define create_event(x) Event event;\
						event.type = x;

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

			void operator()(const unsigned int& width, const unsigned int& height)
			{
				this->width = width;
				this->height = height;
			}
		};			 

		struct TextEvent
		{
			unsigned int text;

			void operator()(const unsigned int& text)
			{
				this->text = text;
			}
		};

		struct KeyboardEvent
		{
			int code;

			void operator()(const int& code)
			{
				this->code = code;
			}
		};
		
		struct MouseScrolledEvent
		{
			double delta;

			void operator()(const double& delta)
			{
				this->delta = delta;
			}
		};

		struct MouseMovedEvent
		{
			double x;
			double y;

			void operator()(const double& x, const double& y)
			{
				this->x = x;
				this->y = y;
			}
		};

		struct MouseButtonEvent
		{
			int button;

			void operator()(const int& button)
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

		Type type;

		union
		{
			SizeEvent			sizeEvent;
			TextEvent			textEvent;
			KeyboardEvent		keyEvent;
			MouseScrolledEvent	mouseScrolledEvent;
			MouseMovedEvent		mouseMovedEvent;
			MouseButtonEvent	mouseButtonEvent;
		};

		std::string toString();
		bool isHandled() const
		{
			return m_handled;
		}
		void hasBeenHandled()
		{
			m_handled = true;
		}
	private:
		bool m_handled = false;
	};

}
