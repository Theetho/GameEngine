#include "EnginePch.h"
#include "RigidBody.h"

namespace Engine
{
	RigidBody::RigidBody(
		GameObject& owner,
		Vec3 position
	)
		: Component(owner)
		, m_position(position)
		, m_rotation(0.0f)
		, m_velocity(0.0f)
	{
	}
	RigidBody::~RigidBody()
	{
	}

	void RigidBody::useGravity(
		bool use
	)
	{
		m_useGravity = use;
	}
}