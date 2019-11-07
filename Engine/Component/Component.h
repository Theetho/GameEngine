#pragma once

namespace Engine
{
	class GameObject;

	class Component
	{
	public:
		enum class Type
		{
			Movement,
			Physics,
			Collider
		};

		Component(
			GameObject& owner
		);

		Component(
			const Component& other
		);

		Component(
			const Component&& other
		) noexcept;

		virtual ~Component();

		virtual void onUpdate(
			const double& delta
		) = 0;

		inline virtual Type getType() = 0;

		inline GameObject& getOwner()
		{
			return m_owner;
		}

	protected:
		GameObject& m_owner;
	};
}

