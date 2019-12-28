#include "EnginePch.h"
#include "Event.h"

namespace Engine
{
	std::string Event::ToString()
	{
		std::stringstream result;

		switch (this->mType)
		{
			case Event::Type::Resized:
				result	<< "Resized this : " 
					<< this->mSizeEvent.width
					<< " " 
					<< this->mSizeEvent.height 
					<< '\n';
				break;
			case Event::Type::Closed:
				result	<< "Closed this\n";
				break;
			case Event::Type::TextEntered:
				result	<< "Text entered this : "
					<< static_cast<char>(this->mTextEvent.text)
					<< '\n';
				break;
			case Event::Type::KeyPressed:
				result	<< "Key pressed this : "
					<< this->mKeyEvent.code
					<< '\n';
				break;
			case Event::Type::KeyReleased:
				result	<< "Key released this : "
					<< this->mKeyEvent.code
					<< '\n';
				break;
			case Event::Type::MouseScrolled:
				result	<< "Mouse scrolled this : "
					<< this->mMouseScrolledEvent.x
					<< " "
					<< this->mMouseScrolledEvent.y
					<< '\n';
				break;
			case Event::Type::MouseMoved:
				result	<< "Mouse moved this : "
					<< this->mMouseMovedEvent.x
					<< " "
					<< this->mMouseMovedEvent.y
					<< '\n';
				break;
			case Event::Type::MouseButtonPressed:
				result	<< "Mouse button pressed this : "
					<< this->mMouseButtonEvent.button
					<< '\n';
				break;
			case Event::Type::MouseButtonReleased:
				result	<< "Mouse button released this : "
					<< this->mMouseButtonEvent.button
					<< '\n';
				break;
			default: 
				result	<< "Unhandled this\n";
				break;
		}

		return result.str();
	}

	bool Event::IsHandled() const
	{
		return mHandled;
	}

	void Event::SetIsHandled(bool handled)
	{
		mHandled = handled;
	}
}