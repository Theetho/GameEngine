#include "pch.h"
#include "GameApplication.h"
#include "Layers/TheChernoLayer.h"

GameApplication::GameApplication()
	: Application()
{
	this->pushLayer(new TheChernoLayer());
}

GameApplication::~GameApplication()
{
}

Engine::Application* Engine::createApplication()
{
	return new GameApplication();
}