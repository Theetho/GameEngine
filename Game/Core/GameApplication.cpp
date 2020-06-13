#include "pch.h"
#include "GameApplication.h"
#include "Layers/GameLayer.h"

GameApplication::GameApplication()
	: Application()
{
	Engine::Shader::SetFolder("./Assets/Shaders/");
	Engine::Texture::SetFolder("./Assets/Textures/");
	Engine::Model::SetFolder("./Assets/Models/");
	this->GetWindow().Maximise();

	this->PushLayer(new GameLayer());
}

GameApplication::~GameApplication()
{}

Engine::Application* Engine::CreateApplication()
{
	return new GameApplication();
}