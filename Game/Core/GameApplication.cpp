#include "pch.h"
#include "GameApplication.h"
#include "Layers/TheChernoLayer.h"

GameApplication::GameApplication()
	: Application()
{
	Engine::Shader::setFolder("Assets/Shaders/");
	Engine::Texture::setFolder("Assets/Textures/");
	this->pushLayer(new TheChernoLayer());
}

GameApplication::~GameApplication()
{
}

Engine::Application* Engine::createApplication()
{
	return new GameApplication();
}