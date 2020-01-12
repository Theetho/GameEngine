#include "Window.h"

using namespace sf;

namespace UILib
{
	Window::Window(unsigned int width, unsigned int height, const std::string& title)
		: mWidth(width)
		, mHeight(height)
	{
		this->create(VideoMode(width, height), String(title));
	}

	Window::~Window()
	{}

	void Window::RenderUI()
	{
		for (auto& uielement : mUIElements)
			this->draw(*uielement);
	}

	void Window::UpdateUI()
	{
		UIElement::UpdateMouseInput(this->mapPixelToCoords(Mouse::getPosition(*this)));
		
		for (auto& uielement : mUIElements)
			uielement->OnUpdate();
	}

	void Window::AddUIElement(UIElement* element)
	{
		mUIElements.push_back(element);
	}

	void Window::Clear(const sf::Color& color)
	{
		this->clear(color);
	}

	bool Window::PollEvent(sf::Event& event)
	{
		if (!this->pollEvent(event))
			return false;

		for (auto& uielement : mUIElements) 
			uielement->OnEvent(event);

		return true;
	}

	void Window::Draw(const sf::Drawable& drawable)
	{
		this->draw(drawable);
	}

	void Window::Display()
	{
		this->display();
	}

	unsigned int Window::GetWidth() const
	{
		return mWidth;
	}

	unsigned int Window::GetHeight() const
	{
		return mHeight;
	}

	std::vector<UIElement*>& Window::GetUIElements()
	{
		return mUIElements;
	}
}
