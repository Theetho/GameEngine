#pragma once

#include "UIElement.h"
#include <iostream>

using namespace sf;

namespace UILib
{
	sf::Font* UIElement::sFont;
	std::unordered_map<const char*, sf::Color> UIElement::sColor{
		{"Background", sf::Color(240, 240, 240)},
		{"Text", sf::Color::Black},
		{"Text_Hover", sf::Color(50, 50, 220)},
		{"Outline", sf::Color::Black},
	};
	UIElement::MouseInput UIElement::sMouse;
	unsigned int UIElement::sInstanceCount = 0;

	UIElement::UIElement(const sf::Vector2f& position, std::function<void()> callback, const std::string& label)
		: mShape(Vector2f(200.f, 20.f))
		, mCallback(std::move(callback))
		, mLabel(label, *sFont)
		, mCallbackType(CallbackType::NONE)
	{
		if (!sFont)
		{
			sFont = new sf::Font;
			sFont->loadFromFile("./UILib/Font/consola.ttf");
			//sFont->loadFromFile("./PTrans/UILib/Font/consola.ttf");
			mLabel.setFont(*sFont);
		}

		mShape.setPosition(position);
		mShape.setFillColor(sColor["Background"]);

		ApplyFont(mLabel, 21);
		mLabel.setPosition(position - sf::Vector2f(mLabel.getGlobalBounds().width + mShape.getSize().x * 0.05f, mShape.getSize().y * 0.25f));
		++sInstanceCount;
	}

	UIElement::UIElement(const UIElement& ui_element)
		: mShape(ui_element.mShape)
		, mCallback(ui_element.mCallback)
	{
		++sInstanceCount;
	}

	UIElement::UIElement(const UIElement&& ui_element) noexcept
		: mShape(ui_element.mShape)
		, mCallback(ui_element.mCallback)
	{
		++sInstanceCount;
	}

	UIElement& UIElement::operator=(const UIElement& ui_element)
	{
		mShape = ui_element.mShape;
		mCallback = ui_element.mCallback;

		++sInstanceCount;

		return *this;
	}

	UIElement& UIElement::operator=(const UIElement&& ui_element) noexcept
	{
		mShape = ui_element.mShape;
		mCallback = ui_element.mCallback;

		++sInstanceCount;

		return *this;
	}

	UIElement::~UIElement()
	{
		--sInstanceCount;
	
		if (sFont && !sInstanceCount)
		{
			delete sFont;
		}
	}

	void UIElement::UpdateMouseInput(const sf::Vector2f& mouse_position)
	{
		auto previous = sMouse.position;
		sMouse.position = mouse_position;
		sMouse.movement = sMouse.position - previous;
	}

	sf::Font* UIElement::GetFont()
	{
		return sFont;
	}

	sf::Color UIElement::GetColor(const char* attribute)
	{
		return sColor.at(attribute);
	}

	void UIElement::OnEvent(const sf::Event& event)
	{

	}

	bool UIElement::Contains(const sf::Vector2f& vector) const
	{
		float left = mShape.getGlobalBounds().left;
		float top = mShape.getGlobalBounds().top;
		float right = left + mShape.getGlobalBounds().width;
		float bottom = top + mShape.getGlobalBounds().height;

		return vector.x >= left && vector.x <= right && vector.y >= top && vector.y <= bottom;
	}

	void UIElement::SetPosition(const sf::Vector2f& position)
	{
		mShape.setPosition(position);
		CenterText(mLabel);
	}

	void UIElement::SetCallbackType(CallbackType callback_type)
	{
		mCallbackType = callback_type;
	}

	void UIElement::CenterText(sf::Text& text)
	{
		sf::Vector2f offset = sf::Vector2f(text.getGlobalBounds().left, text.getGlobalBounds().top) - text.getPosition();

		text.setPosition((mShape.getPosition() + (mShape.getSize() - sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height)) / 2.f) - offset);
	}

	void UIElement::draw(RenderTarget& target, RenderStates states) const
	{
		target.draw(mShape);
		target.draw(mLabel);
	}
}