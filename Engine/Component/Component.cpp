#include "EnginePch.h"
#include "Component.h"

namespace Engine
{
	Component::Component(
		GameObject* owner
	)
		: m_owner(owner)
	{
	}

	Component::~Component()
	{
	}
}