#include "pch.h"
#include "SandboxApplication.h"
#include "Layers/BombermanLayer.h"
//#include "Layers/TerrainLayer.h"

SandboxApplication::SandboxApplication()
	: Application()
{
	Engine::Shader::SetFolder("./Assets/Shaders/");
	Engine::Texture::SetFolder("./Assets/Textures/");
	Engine::Model::SetFolder("./Assets/Models/");
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