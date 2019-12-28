#include "EnginePch.h"
#include "Component.h"

namespace Engine
{
	Component::Component(GameObject& game_object)
		: mGameObject(game_object)
	{}

	Component::Component(const Component& component) 
		: mGameObject(component.mGameObject)
	{}

	Component::Component(const Component&& component) noexcept
		: mGameObject(component.mGameObject)
	{}

	Component::~Component()
	{}

	GameObject& Component::GetGameObject()
	{
		return mGameObject;
	}

	const GameObject& Component::GetGameObject() const
	{
		return mGameObject;
	}
}