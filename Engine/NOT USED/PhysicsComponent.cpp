#include "EnginePch.h"
#include "PhysicsComponent.h"
#include "GameObject/GameObject.h"
#include "Core/Log.h"

namespace Engine
{
	const PhysicsComponent::Force PhysicsComponent::sForce(5.0f, 0.3f);

	PhysicsComponent::PhysicsComponent(
		GameObject& gameObject
	)
		: Component(gameObject)
		, mTransform(gameObject.GetTransform())
		, mGroundLevel(0.0f)
		, m_Jump()
		, mPercentage(1.0f, 1.0f)
	{
		m_Jump.is_jumping = true;
	}

	PhysicsComponent::~PhysicsComponent()
	{
	}

	void PhysicsComponent::OnUpdate(const double& delta)
	{
		//Vec3& position = mTransform.GetPosition();
		//
		//// Gravity
		//if (!m_Jump.is_jumping && (position.y > mGroundLevel))
		//{
		//	position.y -= mPercentage.gravity * sForce.gravity * (float)delta;
		//}
		//// Jump
		//else if (m_Jump.is_jumping)
		//{
		//	position.y   += m_Jump.jump_strengh * delta;
		//	m_Jump.delta += delta;
		//	if (m_Jump.delta >= m_Jump.jump_duration)
		//	{
		//		m_Jump.is_jumping = false;
		//		m_Jump.is_falling = true;
		//		m_Jump.delta = 0;
		//	}
		//}
		//// Only goes here when the object hits the ground
		//else if (m_Jump.is_falling)
		//{
		//	m_Jump.is_falling = false;
		//}

		//mGroundLevel = -1000.0f;
	}

	float PhysicsComponent::GetGravity() const
	{
		return mPercentage.gravity * sForce.gravity;
	}
	
	float PhysicsComponent::GetGroundLevel() const
	{
		return mGroundLevel;
	}
	
	float PhysicsComponent::GetFriction() const
	{
		return mPercentage.friction * sForce.friction;
	}
	
	bool PhysicsComponent::IsInAir() const
	{
		return m_Jump.is_jumping || m_Jump.is_falling;
	}
	
	bool PhysicsComponent::IsJumping() const
	{
		return m_Jump.is_jumping;
	}
	
	bool PhysicsComponent::IsFalling() const
	{
		return m_Jump.is_falling;
	}
	
	void PhysicsComponent::SetGroundLevel(float value)
	{
		mGroundLevel = value;
	}
	
	void PhysicsComponent::SetFrictionPecentage(float percentage)
	{
		mPercentage.friction = percentage;
	}
	
	void PhysicsComponent::SetIsJumping()
	{
		m_Jump.is_jumping = true;
	}
}