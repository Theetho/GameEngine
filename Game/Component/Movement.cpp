#include "pch.h"
#include "Movement.h"

using namespace Engine;

Movement::Movement(GameObject& gameObject)
	: Component(gameObject)
	, mTransform(gameObject.GetTransform())
	, mRotation(0.0f)
{
}

Movement::~Movement()
{}

void Movement::OnUpdate(const double& delta)
{
	auto rigid_body = mGameObject.GetComponent<RigidBody>();
	if (!rigid_body)
		return;
	Vec3& velocity = rigid_body->GetVelocity();

	if (mGameObject.IsColliding())
	{
		mTransform.GetPosition() -= (mAxis["Forward"] * velocity.z) + (mAxis["Side"] * velocity.x);
		mGameObject.SetIsColliding(false);
	}

	velocity.x = 0.0f;
	velocity.z = 0.0f;

	if (Input::IsKeyPressed(ENGINE_KEY_W))
	{
		if (!Input::IsKeyPressed(ENGINE_KEY_S))
		{
			mTransform.GetRotation().y = mRotation + 0.0f;
			velocity.z += mSpeed * delta;
		}
	}
	else if (Input::IsKeyPressed(ENGINE_KEY_S))
	{
		mTransform.GetRotation().y = mRotation + 180.0f;
		velocity.z -= mSpeed * delta;
	}

	if (Input::IsKeyPressed(ENGINE_KEY_A))
	{
		if (!Input::IsKeyPressed(ENGINE_KEY_D))
		{
			mTransform.GetRotation().y = mRotation + 90.0f;
			velocity.x -= mSpeed * delta;
		}
	}
	else if (Input::IsKeyPressed(ENGINE_KEY_D))
	{
		mTransform.GetRotation().y = mRotation + 270.0f;
		velocity.x += mSpeed * delta;
	}

	velocity += (mAxis["Forward"] * velocity.z) + (mAxis["Side"] * velocity.x);
}

void Movement::SetForwardAxis(const Engine::Vec3& axis)
{
	mAxis["Forward"] = glm::normalize(axis);
	mAxis["Side"] = glm::cross(mAxis["Forward"], mAxis["Up"]);

	// the dot product between the forward axis and the z axis is
	// in [-1, 0, 1], which gives [180, 90, 0] with acos.
	mRotation = glm::degrees(std::acos(glm::dot(mAxis["Forward"], Engine::Vec3(0.0f, 0.0f, 1.0f))));

	// as 0 gives only 90 (where it could be 270)
	if (mRotation == 90.0f)
	{
		// we add the dot product between the forward axis and the x axis,
		// which is either 0 or 180, which gives 90 or 270.
		mRotation += glm::degrees(std::acos(glm::dot(mAxis["Forward"], { 1.0f, 0.0f, 0.0f })));
	}
}
