#pragma once

namespace Engine
{
	class GameObject;

	/// Abstract base class

	class Component
	{
	public:
		Component(GameObject& game_object);
		Component(const Component& component);
		Component(const Component&& component) noexcept;
		virtual ~Component();

		virtual void OnUpdate(const double& delta) = 0;

		virtual GameObject&		  GetGameObject();
		virtual const GameObject& GetGameObject() const;

	protected:
		GameObject& mGameObject;
	};
}

