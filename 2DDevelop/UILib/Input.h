#pragma once

#include "UIElement.h"
#include <sstream>
#include <fstream>
#include <limits>

namespace UILib
{
	template<class T>
	class Input : public UIElement
	{
	public:
		Input(T& value, const sf::Vector2f& position, std::function<void()> callback, const std::string& label)
			: UIElement(position, std::move(callback), label)
			, mValue(value)
			, mValueToString()
			, mValueToRender("", *sFont)
			, mIsNumber(std::is_arithmetic<T>::value && !std::is_same<char, T>())
		{
			mValueToString << value;
			mValueToRender.setString(mValueToString.str());
			ApplyFont(mValueToRender, 21);
			CenterText(mValueToRender);
		}
		~Input()
		{}

		void OnUpdate() override
		{
			if (!mIsEditable)
				return;

			// Trigger the listenning state
			if (this->Contains(sMouse.position) && Mouse::isButtonPressed(Mouse::Button::Left))
			{
				mIsListenning = true;
				mValueToString.str("");
				mValueToRender.setString(mValueToString.str());
			}
			// Disable the listenning state
			else if (!this->Contains(sMouse.position) && Mouse::isButtonPressed(Mouse::Button::Left))
			{
				mIsListenning = false;
			}
			// If the value was modified elsewhere
			else if (!mIsListenning)
			{
				mValueToString.str("");
				mValueToString << mValue;

				// Update the displayed value
				mValueToRender.setString(mValueToString.str());
				CenterText(mValueToRender);
			}
		}

		void OnEvent(const sf::Event& event) override
		{
			if (!mIsListenning || !mIsEditable)
				return;

			// Disable the listenning state
			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Enter)
				{
					mIsListenning = false;
				}
			}
			// Catch the new character
			else if (event.type == sf::Event::TextEntered && event.text.unicode < 128)
			{
				if (mValueToRender.getGlobalBounds().width >= mShape.getSize().x)
					return;

				// Filter not number characters if the type is a number
				if (mIsNumber && (event.text.unicode > 57 || event.text.unicode < 48))
					return;

				// Append the new character
				mValueToString << static_cast<char>(event.text.unicode);

				// Then update the value
				std::istringstream caster(mValueToString.str());
				caster >> mValue;

				// Check if the value is not going out of its type limits
				mValueToString.str("");
				mValueToString << mValue;

				// Update the displayed value
				mValueToRender.setString(mValueToString.str());
				CenterText(mValueToRender);
				
				if (mCallback)
					mCallback();
			}
		}

		inline T GetValue() const
		{
			return mValue;
		}

		inline void SetEditable(bool set)
		{
			mIsEditable = set;
		}

	private:
		bool mIsListenning = false;
		bool mIsNumber;
		bool mIsEditable = true;
		T& mValue;
		sf::Text mValueToRender;
		std::stringstream mValueToString;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			UIElement::draw(target, states);
			target.draw(mValueToRender);
		}
	};
}
