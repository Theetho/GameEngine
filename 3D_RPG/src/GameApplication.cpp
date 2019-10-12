#include "../include/GameApplication.h"

GameApplication::GameApplication()
	: Application()
{
}

GameApplication::~GameApplication()
{
}

void GameApplication::run()
{
}

Engine::Application* Engine::createApplication()
{
	return new GameApplication();
}