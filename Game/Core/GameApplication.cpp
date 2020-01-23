#include "pch.h"
#include "GameApplication.h"
#include "Layers/BombermanLayer.h"
#include "Layers/TerrainLayer.h"

GameApplication::GameApplication()
	: Application()
{
	Engine::Shader::SetFolder("./Assets/Shaders/");
	Engine::Texture::SetFolder("./Assets/Textures/");
	Engine::Model::SetFolder("./Assets/Models/");
	this->PushLayer(new TerrainLayer());

	this->GetWindow().SetFullscreen(true);
}

GameApplication::~GameApplication()
{
}

Engine::Application* Engine::CreateApplication()
{
	return new GameApplication();
}