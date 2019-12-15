#include "pch.h"
#include "Movement.h"

using namespace Engine;

Movement::Movement(
	GameObject& owner
)
	: Component(owner)
	, m_transform(owner.getTransform())
{
}

void Movement::onUpdate(const double& delta)
{
	if (m_owner.isColliding())
		m_transform.getPosition() -= m_velocity;

	m_velocity = Vec3(0.0f);

	if (Input::isKeyPressed(ENGINE_KEY_W))
	{
		if (!Input::isKeyPressed(ENGINE_KEY_S))
		{
			m_transform.getRotation().y = 0.0f;
			m_velocity.z = m_speed * delta;
		}
	}
	else if (Input::isKeyPressed(ENGINE_KEY_S))
	{
		m_transform.getRotation().y = 180.0f;
		m_velocity.z = - m_speed * delta;
	}

	if (Input::isKeyPressed(ENGINE_KEY_A))
	{
		if (!Input::isKeyPressed(ENGINE_KEY_D))
		{
			m_transform.getRotation().y = 90.0f;
			m_velocity.x = m_speed * delta;
		}
	}
	else if (Input::isKeyPressed(ENGINE_KEY_D))
	{
		m_transform.getRotation().y = 270.0f;
		m_velocity.x = - m_speed * delta;
	}

	m_transform.getPosition() += m_velocity;

	m_transform.updateModel();
}
