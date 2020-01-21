#include "pch.h"
#include "Player.h"
#include "Component/Movement.h"

using namespace Engine;

Player::Player(Ref<Model> model, const Transform& transform)
	: GameObject(transform)
{
	AddComponent<RigidBody>(CreateRef<RigidBody>(*this));
	GetComponent<RigidBody>()->GetTransform().SetRotation('y', 1.0f);
	AddComponent<Movement>(CreateRef<Movement>(*this));

	this->SetModel(model);
	std::cout << "Player : " << mTransform.GetPosition();
	std::cout << " " << mTransform.GetRotation();
	std::cout << " " << mTransform.GetScale() << std::endl;
}

Player::~Player()
{}

void Player::OnUpdate(const double& delta)
{
	GameObject::OnUpdate(delta);
}

void Player::OnEvent(Engine::Event& event)
{
	if (event.mType == Engine::Event::KeyPressed)
	{
		if (event.mKeyEvent.code == ENGINE_KEY_SPACE)
		{
			Ref<Bomb> bomb = CreateRef<Bomb>(AssetManager::GetModelLibrary().Get("bomb"), mTransform, mBombPower);

			// Translate the bomb so the bottom is just on the floor
			float floor_level = mTransform.GetPosition().y - (mModel->GetSize().y * mTransform.GetScale().y / 2.0f);

			bomb->SetPosition({
				bomb->GetTransform().GetPosition().x,
				floor_level + (bomb->GetModel().GetSize().y * bomb->GetTransform().GetScale().y / 2.0f),
				bomb->GetTransform().GetPosition().z
			});

			mBombs.push_back(std::move(bomb));
		}
		//// TEMPORARY
		//if (event.mKeyEvent.code == ENGINE_KEY_Q)
		//{
		//	mBombPower += 1.0;
		//	std::cout << "Player's bombs power : " << mBombPower << std::endl;
		//}
	}
}

void Player::OnCollision(const Engine::Collision& collision)
{
	if (collision.IsColliding)
	{
		auto rigid_body = GetComponent<RigidBody>();
		rigid_body->GetTransform().SetPosition('y', collision.PenetrationDistance.y);
	}
}

const Engine::Ref<Engine::Model> Player::GetModel() const
{
	return mModel;
}

std::vector<Engine::Ref<Bomb>>& Player::GetBombs()
{
	return mBombs;
}

bool Player::IsMoveable() const
{
	return true;
}

void Player::SetModel(Engine::Ref<Engine::Model> model)
{
	mModel = model;

	Vec3 size = model->GetSize();

	AddComponent<BoxCollider>(CreateRef<BoxCollider>(*this, mTransform.GetPosition(), Vec3(size.x, size.y, size.z)));
}

void Player::Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const
{
	GameObject::Render(render_command, shader);
	Renderable::Render(mModel, render_command, shader);
}
