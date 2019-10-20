#include "EnginePch.h"
#include "..\include\Event.h"

namespace Engine
{
	std::string EventToString(Event* event)
	{
		std::stringstream ss;

		switch (event->type)
		{
			case Event::Type::Resized:
				ss	<< "Resized event : " 
					<< event->sizeEvent.width
					<< " " 
					<< event->sizeEvent.height 
					<< '\n';
				break;
			case Event::Type::Closed:
				ss	<< "Closed event\n";
				break;
			case Event::Type::TextEntered:
				ss	<< "Text entered event : "
					<< static_cast<char>(event->textEvent.text)
					<< '\n';
				break;
			case Event::Type::KeyPressed:
				ss	<< "Key pressed event : "
					<< event->keyEvent.code
					<< '\n';
				break;
			case Event::Type::KeyReleased:
				ss	<< "Key released event : "
					<< event->keyEvent.code
					<< '\n';
				break;
			case Event::Type::MouseScrolled:
				ss	<< "Mouse scrolled event : "
					<< event->mouseScrolledEvent.delta
					<< '\n';
				break;
			case Event::Type::MouseMoved:
				ss	<< "Mouse moved event : "
					<< event->mouseMovedEvent.x
					<< " "
					<< event->mouseMovedEvent.y
					<< '\n';
				break;
			case Event::Type::MouseButtonPressed:
				ss	<< "Mouse button pressed event : "
					<< event->mouseButtonEvent.button
					<< '\n';
				break;
			case Event::Type::MouseButtonReleased:
				ss	<< "Mouse button released event : "
					<< event->mouseButtonEvent.button
					<< '\n';
				break;
			default: 
				ss	<< "Unhandled event\n";
				break;
		}

		return ss.str();
	}

	std::string Engine::Event::toString()
	{
		return EventToString(this);
	}

}