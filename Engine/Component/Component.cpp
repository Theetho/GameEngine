#include "EnginePch.h"
#include "Component.h"

namespace Engine
{
	Component::Component(
		GameObject& owner
	)
		: m_owner(owner)
	{
	}

	Component::Component(
		const Component& other
	) 
		: m_owner(other.m_owner)
	{
	}

	Component::Component(
		const Component&& other
	) noexcept
		: m_owner(other.m_owner)
	{
	}

	Component::~Component()
	{
	}
}