#include "pch.h"
#include "GameApplication.h"
#include "Layers/BombermanLayer.h"

GameApplication::GameApplication()
	: Application()
{
	Engine::Shader::SetFolder("./Assets/Shaders/");
	Engine::Texture::SetFolder("./Assets/Textures/");
	Engine::Model::SetFolder("./Assets/Models/");
	this->PushLayer(new BombermanLayer());

	this->GetWindow().SetFullscreen(true);
}

GameApplication::~GameApplication()
{
}

Engine::Application* Engine::CreateApplication()
{
	return new GameApplication();
}