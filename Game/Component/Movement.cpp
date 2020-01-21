#include "pch.h"
#include "Movement.h"

using namespace Engine;

Movement::Movement(GameObject& game_object, bool is_reversed)
	: Component(game_object)
	, mRigidBody(game_object.GetComponent<RigidBody>())
	, mIsReversed(is_reversed)
{
}

Movement::~Movement()
{}

void Movement::OnUpdate(const double& delta)
{
	if (!mRigidBody)
		return;

	Transform& transform = mRigidBody->GetTransform();
	Vec3& velocity		 = mRigidBody->GetVelocity();
	Vec3& angular		 = mRigidBody->GetAngularVelocity();
	
	velocity.x = 0.0f;; velocity.z = 0.0f;;
	if (!mRigidBody->IsUsingGravity())
		velocity.y = 0.0f;

	angular = Vec3();

	if (Input::IsKeyPressed(ENGINE_KEY_LEFT_SHIFT))
		mSpeed.current = mSpeed.max;
	else
		mSpeed.current = mSpeed.min;

	if (Input::IsKeyPressed(ENGINE_KEY_W))
	{
		if (!Input::IsKeyPressed(ENGINE_KEY_S))
		{
			velocity.x += mSpeed.current * delta;
		}
	}
	else if (Input::IsKeyPressed(ENGINE_KEY_S))
	{
		velocity.x -= mSpeed.current * delta;
	}

	if (Input::IsKeyPressed(ENGINE_KEY_A))
	{
		if (!Input::IsKeyPressed(ENGINE_KEY_D))
		{
			velocity.z -= mSpeed.current * delta;
		}
	}
	else if (Input::IsKeyPressed(ENGINE_KEY_D))
	{
		velocity.z += mSpeed.current * delta;
	}

	if (Input::IsKeyPressed(ENGINE_KEY_SPACE))
	{
		if (!Input::IsKeyPressed(ENGINE_KEY_LEFT_CONTROL))
		{
			velocity.y += mSpeed.current * delta;
		}
	}
	else if (Input::IsKeyPressed(ENGINE_KEY_LEFT_CONTROL))
	{
		velocity.y -= mSpeed.current * delta;
	}

	if (Input::IsKeyPressed(ENGINE_KEY_E))
	{
		angular.y += (mIsReversed ? mSpeed.angular : - mSpeed.angular) * delta;
	}
	else if (Input::IsKeyPressed(ENGINE_KEY_Q))
	{
		angular.y += (mIsReversed ? - mSpeed.angular : mSpeed.angular) * delta;
	}

	float theta = glm::radians(mIsReversed ? 180 - transform.GetRotation().y : transform.GetRotation().y);
	float dx = velocity.x * sin(theta) - velocity.z * cos(theta);
	float dz = velocity.x * cos(theta) + velocity.z * sin(theta);

	velocity = Vec3(dx, velocity.y, dz);
}

/* MOVEMENT TO GET FOR BOMBERMAN GAME

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
} */
