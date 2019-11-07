#pragma once

#include "Transform.h"
#include "Renderer/Material.h"
#include "Renderer/Texture.h"
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

		// Return 'this' so it is possible to 
		// concatenate setters
		inline GameObject& setTransform(
			const Transform& transform
		)
		{
			m_transform = transform;
			return *this;
		}

		inline Transform& getTransform()
		{
			return m_transform;
		}

		inline const Transform& getTransform() const
		{
			return m_transform;
		}

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

	class DynamicObject : public GameObject
	{
	public:
		DynamicObject(
			const Transform& transform = Transform()
		);
		virtual ~DynamicObject()
		{
		}

		inline void setDirection(
			const Vec3& direction
		)
		{
			m_direction = direction;
		}

		inline const Vec3& getDirection() const
		{
			return m_direction;
		}

	protected:
		Vec3 m_direction;
	};
}

