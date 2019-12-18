#include "pch.h"
#include "Movement.h"

using namespace Engine;

Movement::Movement(
	GameObject& owner
)
	: Component(owner)
	, m_transform(owner.getTransform())
	, m_velocity()
	, m_rotation(0.0f)
{
}

void Movement::onUpdate(const double& delta)
{
	if (m_owner.isColliding())
	{
		m_transform.getPosition() -= (m_axis["Forward"] * m_velocity.z) + (m_axis["Side"] * m_velocity.x);
		m_owner.isColliding(false);
	}

	m_velocity = Vec3(0.0f);

	if (Input::isKeyPressed(ENGINE_KEY_W))
	{
		if (!Input::isKeyPressed(ENGINE_KEY_S))
		{
			m_transform.getRotation().y = m_rotation + 0.0f;
			m_velocity.z += m_speed * delta;
		}
	}
	else if (Input::isKeyPressed(ENGINE_KEY_S))
	{
		m_transform.getRotation().y = m_rotation + 180.0f;
		m_velocity.z -= m_speed * delta;
	}

	if (Input::isKeyPressed(ENGINE_KEY_A))
	{
		if (!Input::isKeyPressed(ENGINE_KEY_D))
		{
			m_transform.getRotation().y = m_rotation + 90.0f;
			m_velocity.x -= m_speed * delta;
		}
	}
	else if (Input::isKeyPressed(ENGINE_KEY_D))
	{
		m_transform.getRotation().y = m_rotation + 270.0f;
		m_velocity.x += m_speed * delta;
	}

	m_transform.getPosition() += (m_axis["Forward"] * m_velocity.z) + (m_axis["Side"] * m_velocity.x);
	m_transform.updateModel();
}
