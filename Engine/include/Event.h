#pragma once

#include "Export.h"

#define BIT(x) x << 1

// Event class header based on the SFML Event class and the one in The Cherno serie

namespace Engine
{
	class ENGINE_API Event
	{
	public:
		struct SizeEvent
		{
			unsigned int width;
			unsigned int height;
		};

		struct TextEvent
		{
			unsigned int text;
		};

		struct KeyboardEvent
		{
			int code;
		};
		
		struct MouseScrolled
		{
			float delta;
		};

		struct MouseMovedEvent
		{
			unsigned int x;
			unsigned int y;
		};

		struct MouseButtonEvent
		{
			int code;
		};

		enum Type
		{
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
			KeyboardEvent			keyEvent;
			MouseMovedEvent		mouseMovedEvent;
			MouseButtonEvent	mouseButtonEvent;
		};
	private:
		bool m_handled = false;
	};

}
