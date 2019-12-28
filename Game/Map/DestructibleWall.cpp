#include "pch.h"
#include "DestructibleWall.h"

using namespace Engine;

Ref<Model> DestructibleWall::sModel;
bool DestructibleWall::sIsInitialized = false;

DestructibleWall::DestructibleWall(const Transform& transform)
	: Wall(transform)
{
	if (!sIsInitialized)
	{
		sIsInitialized = true;

		sModel = AssetManager::GetModelLibrary().Load("cube/cube.obj", "destructible_wall");

		auto texture = std::vector<Ref<Texture2D>>({ AssetManager::GetTexture2DLibrary().Load("snow.jpg") });

		sModel->SetMaterial(std::make_shared<PBRMaterial>(texture, texture, texture, texture));
	}
}

DestructibleWall::~DestructibleWall()
{}

bool DestructibleWall::IsEnabled() const
{
	return mEnable;
}

void DestructibleWall::Explode()
{
	this->hasExploded = true;
	// We hide the wall and destroy its collider
	// before removing it from the world
	this->Disable();
}

void DestructibleWall::Disable()
{
	RemoveComponent<Engine::BoxCollider>();
	mEnable = false;
}

const Engine::Ref<Engine::Model> DestructibleWall::GetModel() const
{
	return sModel;
}
