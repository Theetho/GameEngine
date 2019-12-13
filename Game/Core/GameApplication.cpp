#include "pch.h"
#include "GameApplication.h"
#include "Layers/BombermanLayer.h"
#include "Layers/MapLayer.h"

GameApplication::GameApplication()
	: Application()
{
	Engine::Shader::setFolder("./Assets/Shaders/");
	Engine::Texture::setFolder("./Assets/Textures/");
	Engine::Model::setFolder("./Assets/Models/");
	this->pushLayer(new BombermanLayer());

	//this->getWindow().setFullscreen(true);
}

GameApplication::~GameApplication()
{
}

Engine::Application* Engine::createApplication()
{
	return new GameApplication();
}