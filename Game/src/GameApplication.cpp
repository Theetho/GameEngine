#include "pch.h"
#include "GameApplication.h"

GameApplication::GameApplication()
	: Application()
{
}

GameApplication::~GameApplication()
{
}

Engine::Application* Engine::createApplication()
{
	return new GameApplication();
}