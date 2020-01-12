#pragma once

#include "UIElement.h"

namespace UILib
{
	template<class T>
	class Slider : public UIElement
	{
	public:
		Slider(T& value, T min, T max, T step, sf::Vector2f position, std::function<void()> callback, const std::string& label)
			: UIElement(position, std::move(callback), label)
			, mMax(max)
			, mMin(min)
			, mValue(value)
			, mValueText("", *sFont)
			, mValueStep(step)
			, mCursorTranslation(0.0)
		{
			mShape.setFillColor(sf::Color::Transparent);

			mLine.setSize(sf::Vector2f(mShape.getSize().x * 0.5f, mShape.getSize().y * 0.25f));
			mLine.setPosition(sf::Vector2f(position.x * 1.05f, position.y + (mShape.getSize().y - mLine.getSize().y) / 2.0f));
			mLine.setFillColor(sf::Color(128, 128, 128));
			mLine.setOutlineColor(sf::Color(40, 40, 40));
			mLine.setOutlineThickness(1);

			DisplayValue(mValue, mValueText);
			ApplyFont(mValueText, 21);

			mValueText.setPosition(sf::Vector2f(mLine.getPosition().x + mLine.getSize().x * 1.1f, position.y - mShape.getSize().y * 0.25f));

			mCursor.setRadius(6);
			mCursor.setPosition(sf::Vector2f(mLine.getPosition().x + ((mValue - mMin) / (mMax - mMin)) * mLine.getSize().x - mCursor.getRadius(), position.y + (mShape.getSize().y / 2.0f - mCursor.getRadius())));
			mCursor.setFillColor(sf::Color(200, 200, 200));
			mCursor.setOutlineColor(sf::Color(40, 40, 40));
			mCursor.setOutlineThickness(1);

			mCursorStep = mLine.getGlobalBounds().width / ((mMax - mMin) / mValueStep);
		}
		void OnUpdate() override
		{
			if (this->Contains(sMouse.position) && Mouse::isButtonPressed(Mouse::Button::Left))
			{
				mCursorTranslation += sMouse.movement.x;

				if (std::abs(mCursorTranslation) > mCursorStep)
				{
					int factor = std::abs(mCursorTranslation) / mCursorStep;
					mCursor.setPosition(mCursor.getPosition() + Vector2f((double)factor * (mCursorTranslation < 0.0 ? -mCursorStep : mCursorStep), 0.0f));
					mValue += (T)factor * (mCursorTranslation < 0.0 ? -mValueStep : mValueStep);
					mCursorTranslation = fmodf(mCursorTranslation, mCursorStep);
				}

				float min_x = mLine.getPosition().x - mCursor.getRadius();
				float max_x = min_x + mLine.getGlobalBounds().width;
				float cursor_x = mCursor.getPosition().x;
				mValue = mValue > mMax ? mMax : mValue < mMin ? mMin : mValue;

				DisplayValue(mValue, mValueText);

				mCursor.setPosition(sf::Vector2f(std::max(std::min(max_x, cursor_x), min_x), mCursor.getPosition().y));
				if (mCallback)
					mCallback();
			}
		}
		double GetValue() const
		{
			return mValue;
		}
	private:
		T  mMin;
		T  mMax;
		T& mValue;
		T  mValueStep;
		double mCursorTranslation;
		double mCursorStep;
		sf::Text		   mValueText;
		sf::RectangleShape mLine;
		sf::CircleShape    mCursor;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			UIElement::draw(target, states);
			target.draw(mLine);
			target.draw(mCursor);
			target.draw(mValueText);
		}
	};
}