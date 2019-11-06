#pragma once

namespace Engine
{
	class GameObject;

	class Component
	{
	public:
		Component(
			GameObject* owner
		);
		virtual ~Component();

		virtual void onUpdate(
			const double& delta
		) = 0;

		inline virtual std::string getName() = 0;
	protected:
		GameObject* m_owner;
	};
}

