#pragma once

#include "Core/Scene/EditableObject.h"

namespace Engine
{
	template<int dimension>
	class GameObject;

	/// Abstract base class

	template<int dimension>
	class Component : public EditableObject
	{
	public:
		Component(GameObject<dimension>& game_object)
			: mGameObject(game_object)
		{}
		Component(const Component& component)
			: mGameObject(component.mGameObject)
		{}
		Component(const Component&& component) noexcept
			: mGameObject(component.mGameObject)
		{}
		Component& operator=(const Component& component)
		{
			mGameObject = component.mGameObject;
			return *this;
		}
		Component& operator=(const Component&& component) noexcept
		{
			mGameObject = component.mGameObject;
			return *this;
		}
		
		~Component() {}
		
		virtual void OnUpdate(const double& delta) = 0;
		
		inline GameObject<dimension>& GetGameObject()
		{
			return mGameObject;
		}
		inline const GameObject<dimension>& GetGameObject() const
		{
			return mGameObject;
		}
	protected:
		GameObject<dimension>& mGameObject;
	};

	template class Component<3>;
	template class Component<2>;

	using Component3D = Component<3>;
	using Component2D = Component<2>;
}

