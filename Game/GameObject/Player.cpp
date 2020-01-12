#include "pch.h"
#include "Player.h"
#include "Component/Movement.h"

using namespace Engine;

Player::Player(Ref<Model> model, const Transform& transform
)
	: GameObject(transform)
{
	AddComponent<Movement>(CreateRef<Movement>(*this));
	AddComponent<RigidBody>(CreateRef<RigidBody>(*this));

	this->SetModel(model);
}

Player::~Player()
{}

void Player::OnUpdate(const double& delta)
{
	GameObject::OnUpdate(delta);
	float& height = mTransform.GetPosition().y;
	float ground_level = GetComponent<RigidBody>()->GetGroundLevel();
	
	if (height - mModel->GetSize().y * mTransform.GetScale().y < ground_level)
		height = ground_level + mModel->GetSize().y * mTransform.GetScale().y;

	mTransform.UpdateModel();
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
		// TEMPORARY
		if (event.mKeyEvent.code == ENGINE_KEY_Q)
		{
			mBombPower += 1.0;
			std::cout << "Player's bombs power : " << mBombPower << std::endl;
		}
	}
}

void Player::OnCollision(const Engine::Collision& collision)
{
	const float epsilon = 0.05f;

	const auto& colliders = collision.GetColliders();

	const Collider* myCollider = &collision.GetColliders().first->GetGameObject() == this
		? colliders.first : colliders.second;
	const Collider* otherCollider = &collision.GetColliders().first->GetGameObject() == this
		? colliders.second : colliders.first;

	// If they are close enough on the up axis, then
	// myCollider is on top of the other (collision
	// with the floor)
	//if (collision.GetDistanceUpAxis() < epsilon)
	//{
	//	auto physics = GetComponent<PhysicsComponent>();
	//
	//	if (physics)
	//		physics->SetGroundLevel(otherCollider->GetMax().y + myCollider->GetCenter().y - myCollider->GetMin().y);
	//}

	// Else, it is a true collision
	//else
	//	mIsColliding = true;
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
