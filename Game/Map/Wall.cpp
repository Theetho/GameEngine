#include "pch.h"
#include "Wall.h"

using namespace Engine;

Ref<Model> Wall::sModel;
bool Wall::sIsInitialized = false;

Wall::Wall(const Transform& transform)
	: GameObject(transform)
{
	if (!sIsInitialized)
	{
		sIsInitialized = true;

		sModel = AssetManager::GetModelLibrary().Load("cube/cube.obj", "wall");

		auto texture = std::vector<Ref<Texture2D>>({ AssetManager::GetTexture2DLibrary().Load("wall.jpg", "wall") });

		sModel->SetMaterial(std::make_shared<PBRMaterial>(texture, texture, texture, texture));
	}

	Vec3 size = sModel->GetSize() * mTransform.GetScale();

	this->AddComponent<BoxCollider>(std::make_shared<BoxCollider>(*this, mTransform.GetPosition(), Vec3(size.x, size.y, size.z)));
}

Wall::~Wall()
{}

const Engine::Ref<Engine::Model> Wall::GetModel() const
{
	return Wall::sModel;
}
