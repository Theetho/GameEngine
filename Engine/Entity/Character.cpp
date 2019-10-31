#include "EnginePch.h"
#include "Character.h"
#include "Core/Input.h"

namespace Engine
{
	Character::Character()
		: Entity()
		, m_cameraController()
	{
	}

	Character::~Character()
	{
	}

	void Character::onUpdate(
		const double& delta
	)
	{
		m_cameraController.onUpdate(delta);
		m_transform.setPosition(m_cameraController.getTransform().getPosition());
	}
}