#pragma once

#include "SFML/Graphics.hpp"

struct CWindow
{
	static sf::RenderWindow mWindow;
	static void Initialize(const sf::VideoMode& videoMode, const sf::String& title);
};

