#pragma once

#include "UIElement.h"

namespace UILib
{
	class Button : public UIElement
	{
	public:
		Button(const sf::Vector2f& position, std::function<void()> callback, const std::string& label)
			: UIElement(position, std::move(callback), label)
		{
			mShape.setOutlineColor(sColor["Outline"]);
			mShape.setOutlineThickness(2);

			CenterText(mLabel);
			//mLabel.setPosition(sf::Vector2f(position.x + (mShape.getSize().x - mLabel.getGlobalBounds().width) / 2.f, position.y - mShape.getSize().y * 0.25f));
		}
		~Button()
		{
		}
		void OnUpdate() override
		{
			mLabel.setFillColor(sColor["Text"]);
			if (this->Contains(sMouse.position))
			{
				mLabel.setFillColor(sColor["Text_Hover"]);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					mClick = true;
				}
				else if (mClick)
				{
					if (mCallback)
						mCallback();
					mClick = false;
				}
			}
		}

	private:
		bool mClick = false;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			UIElement::draw(target, states);
		}
	};
}