#include "pch.h"
#include "ExitCell.h"

using namespace Engine;

Ref<Model> ExitCell::sModel;
bool ExitCell::sIsInitialized = false;

ExitCell::ExitCell(const Transform& transform)
	: Floor(transform)
{
	if (!sIsInitialized)
	{
		sIsInitialized = true;

		sModel = AssetManager::GetModelLibrary().Load("stairs/stairs.obj", "stairs");

		auto texture = std::vector<Ref<Texture2D>>({ AssetManager::GetTexture2DLibrary().Load("wall.jpg", "wall") });

		sModel->SetMaterial(std::make_shared<PBRMaterial>(texture, texture, texture, texture));
	}
	mTransform.SetScale(mTransform.GetScale() * 0.5f);
	mTransform.SetRotation({ 0.0f, 90.0f, 0.0f });

	Vec3 size = sModel->GetSize() * mTransform.GetScale();

	RemoveComponent<BoxCollider>();
}

ExitCell::~ExitCell()
{}

const Engine::Ref<Engine::Model> ExitCell::GetModel() const
{
	return sModel;
}

void ExitCell::Render(Engine::Ref<Engine::RenderCommand> render_command, Engine::Ref<Engine::Shader> shader) const
{
	GameObject::Render(render_command, shader);
	Renderable::Render(sModel, render_command, shader);
}
