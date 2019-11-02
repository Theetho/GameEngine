#include "EnginePch.h"
#include "CameraController.h"
#include "Core/Input.h"
#include "Component.h"

namespace Engine
{
	CameraController::CameraController()
		: GameObject()
		, m_offset(0.0f, 0.0f, 0.0f)
	{
		m_components.push_back(new Engine::PhysicsComponent(this));
		m_components.push_back(new Engine::MovementComponent(this));
	}

	CameraController::~CameraController()
	{
	}

	void CameraController::onUpdate(
		const double& delta
	)
	{
		GameObject::onUpdate(delta);
	}

	void CameraController::onEvent(Event& event)
	{
		if (event.type == Event::KeyPressed && event.keyEvent.code == ENGINE_KEY_SPACE)
		{
			getComponent<PhysicsComponent>()->jump();
		}
	}
}