#include "pch.h"
#include "GameApplication.h"
#include "Layers/GameLayer.h"

GameApplication::GameApplication()
	: Application()
{
	Engine::AssetManager::GetShaderLibrary().SetFolder("./Assets/Shaders/");
	Engine::AssetManager::GetTexture2DLibrary().SetFolder("./Assets/Textures/");
	Engine::AssetManager::GetMeshLibrary().SetFolder("./Assets/Models/");
	this->GetWindow().Maximise();

	this->PushLayer(new GameLayer());
}

GameApplication::~GameApplication()
{}

Engine::Application* Engine::CreateApplication()
{
	return new GameApplication();
}