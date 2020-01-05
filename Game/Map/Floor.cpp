#include "pch.h"
#include "Floor.h"

using namespace Engine;

Ref<Model> Floor::sModel;
bool Floor::sIsInitialized = false;

Floor::Floor(const Transform& transform)
	: GameObject(transform)
{
	if (!sIsInitialized)
	{
		sIsInitialized = true;

		sModel = AssetManager::GetModelLibrary().Load("cube/cube.obj", "floor");

		auto texture = AssetManager::GetTexture2DLibrary().Load("lawn.png");

		sModel->SetMaterial(std::make_shared<PBRMaterial>(texture, texture, texture, texture));
	}

	Vec3 size = sModel->GetSize() * mTransform.GetScale();

	this->AddComponent<BoxCollider>(std::make_shared<BoxCollider>(*this, mTransform.GetPosition(), Vec3(size.x, size.y, size.z)));
}

Floor::~Floor()
{}

const Engine::Ref<Engine::Model> Floor::GetModel() const
{
	return sModel;
}

void Floor::Render(Engine::Ref<Engine::RenderCommand> render_command, Engine::Ref<Engine::Shader> shader) const
{
	GameObject::Render(render_command, shader);
	Renderable::Render(sModel, render_command, shader);
}
