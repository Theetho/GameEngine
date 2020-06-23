#include "pch.h"
#include "SandboxApplication.h"
#include "Layers/BombermanLayer.h"
//#include "Layers/TerrainLayer.h"

SandboxApplication::SandboxApplication()
	: Application()
{
	Engine::AssetManager::GetShaderLibrary().SetFolder("./Assets/Shaders/");
	Engine::AssetManager::GetTexture2DLibrary().SetFolder("./Assets/Textures/");
	Engine::AssetManager::GetMeshLibrary().SetFolder("./Assets/Models/");
	this->GetWindow().Maximise();
	this->PushLayer(new BombermanLayer());

	//this->GetWindow().SetFullscreen(true);
}

SandboxApplication::~SandboxApplication()
{
}

Engine::Application* Engine::CreateApplication()
{
	return new SandboxApplication();
}