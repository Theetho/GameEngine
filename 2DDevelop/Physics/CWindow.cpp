#include "CWindow.h"

sf::RenderWindow CWindow::mWindow;

void CWindow::Initialize(const sf::VideoMode& videoMode, const sf::String& title)
{
	mWindow.create(videoMode, title);
}
