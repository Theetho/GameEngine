#pragma once

#include "Transform.h"
#include "Component/Component.h"

namespace Engine
{
	class GameObject
	{
	public:
		explicit GameObject(
			const Transform& transform = Transform()
		);
		
		GameObject(
			const GameObject& other
		);

		GameObject(
			const GameObject&& other
		) noexcept;
		
		GameObject& operator=(
			const GameObject& other
		);

		GameObject& operator=(
			const GameObject&& other
		) noexcept;

		virtual ~GameObject();

		virtual void onUpdate(
			const double& delta
		);

		virtual void onEvent(
			Event& event
		);

		virtual bool isJumping() const;

		virtual bool isMoving() const;

		virtual bool isColliding() const
		{
			return m_isColliding;
		}
		
		virtual void isColliding(
			const bool& is
		)
		{
			m_isColliding = is;
		}

		inline Transform& getTransform()
		{
			return m_transform;
		}

		inline const Transform& getTransform() const
		{
			return m_transform;
		}

		inline void setPosition(
			const Vec3& position
		)
		{
			m_transform.setPosition(position);
		}
		
		inline void setRotation(
			const Vec3& rotation
		)
		{
			m_transform.setRotation(rotation);
		}
		
		inline void setScale(
			const float& scale
		)
		{
			setScale(Vec3(scale));
		}

		void setScale(
			const Vec3& scale
		);

		template<Component::Type type, typename T>
		std::variant<Ref<T>, void*> getComponent(
		)
		{
			static_assert(std::is_base_of<Component, T>::value, "T is not a component");
		
			std::variant<Ref<T>, void*> result;
			
			result = static_cast<void*>(nullptr);
			
			for (auto component : m_components)
			{
				if (component->getType() == type)
				{
					result = std::dynamic_pointer_cast<T>(component);
					break;
				}
			}

			return result;
		}

		template<Component::Type type, typename T>
		const std::variant<Ref<T>, void*> getComponent(
		) const
		{
			static_assert(std::is_base_of<Component, T>::value, "T is not a component");
			
			std::variant<Ref<T>, void*> result;

			result = static_cast<void*>(nullptr);
			
			for (auto component : m_components)
			{
				if (component->getType() == type)
				{
					result = std::dynamic_pointer_cast<T>(component);
					break;
				}
			}

			return result;
		}

	protected:
		Transform m_transform;
		bool      m_isColliding;
		std::vector<Ref<Component>> m_components;
	};
}

