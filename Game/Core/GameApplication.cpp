#include "pch.h"
#include "GameApplication.h"
#include "Layers/MazeLayer.h"

GameApplication::GameApplication()
	: Application()
{
	Engine::Shader::setFolder("./Assets/Shaders/");
	Engine::Texture::setFolder("./Assets/Textures/");
	Engine::Model::setFolder("./Assets/Models/");
	this->pushLayer(new MazeLayer());
}

GameApplication::~GameApplication()
{
}

Engine::Application* Engine::createApplication()
{
	return new GameApplication();
}