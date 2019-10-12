#include "Window.h"

#include <string>
#include "../include/ConfigFile.h"

Engine::ConfigFile cf("\
width: 1920\n\
height: 1080\n\
title: window\n\
depthBit: 24\n\
stencilBit: 8\n\
antialiasingLevel: 4\n\
majorVersion: 3\n\
minorVersion: 3\n");

Engine::Window::Window()
	: m_window()
{
	this->create();
}
Engine::Window::~Window()
{
}
void Engine::Window::create()
{
	m_window.create(
		sf::VideoMode(cf.get_int(1), cf.get_int(2)),
		cf.get_str(3),
		sf::Style::Default,
		sf::ContextSettings(cf.get_int(4), cf.get_int(5), cf.get_int(6), cf.get_int(7), cf.get_int(8))
	);
}