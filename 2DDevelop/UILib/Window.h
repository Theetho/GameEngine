#pragma once

#include "UIElement.h"

namespace UILib
{
	class Window : private sf::RenderWindow
	{
	public:
		Window(unsigned int width, unsigned int height, const std::string& title);
		~Window();

		void RenderUI();
		void UpdateUI();
		void AddUIElement(UIElement* element);
		void Clear(const sf::Color& color = sf::Color(200, 200, 200));
		bool PollEvent(sf::Event& event);
		void Draw(const sf::Drawable& drawable);
		void Display();

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;
		std::vector<UIElement*>& GetUIElements();
	private:
		unsigned int mWidth;
		unsigned int mHeight;
		std::vector<UIElement*> mUIElements;
	};

}

