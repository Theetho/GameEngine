#pragma once

#include "SFML/include/SFML/Graphics.hpp"
#include "SFML/include/SFML/Window.hpp"
#include <unordered_map>
#include <functional>

#define DisplayValue(value, text) std::stringstream string;\
								  string << value;\
								  text.setString(string.str())
#define ApplyFont(text, size) text.setCharacterSize(size);\
							  text.setStyle(sf::Text::Regular);\
							  text.setFillColor(UILib::UIElement::GetColor("Text"))

namespace UILib
{
	class UIElement : public sf::Drawable
	{
	public:
		UIElement(const UIElement& ui_element);
		UIElement(const UIElement&& ui_element) noexcept;
		UIElement& operator=(const UIElement& ui_element);
		UIElement& operator=(const UIElement&& ui_element) noexcept;
		virtual ~UIElement();

		static void UpdateMouseInput(const sf::Vector2f& mouse_position);
		static sf::Font* GetFont();
		static sf::Color GetColor(const char* attribute);

		virtual void OnUpdate() = 0;
		virtual void OnEvent(const sf::Event& event);
		virtual bool Contains(const sf::Vector2f& vector) const;
	
		virtual void SetPosition(const sf::Vector2f& position);
	protected:
		static sf::Font* sFont;
		static std::unordered_map<const char*, sf::Color> sColor;
		struct MouseInput
		{
			sf::Vector2f position;
			sf::Vector2f movement;
		};
		static MouseInput sMouse;

		sf::RectangleShape mShape;
		sf::Text mLabel;
		std::function<void()> mCallback;

		UIElement(const sf::Vector2f& position, std::function<void()> callback, const std::string& label);
		void CenterText(sf::Text& text);

		// Inherited from Drawable
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		static unsigned int sInstanceCount;
	};
}