#pragma once

#include "Transform.h"
#include "Component/Component.h"

namespace Engine
{
	class Collision;

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

		virtual void onCollision(
			const Collision& collision
		);

		virtual bool isJumping() const;

		virtual bool isMoving() const;

		virtual bool isMoveable() const;

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

		inline const Vec3& getFront() const
		{
			return Vec3(
				sin(glm::radians(m_transform.getRotation().y)),
				0.0f,
				cos(glm::radians(m_transform.getRotation().y))
			);
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

	template<typename T>
	void AddComponent(
		Ref<Component> component
	)
	{
		static_assert(std::is_base_of<Component, T>::value, "T is not a component");

		if (m_components.find(typeid(T)) == m_components.end())
			m_components[typeid(T)] = component;
	}

	template<typename T>
	Ref<T> GetComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "T is not a component");

		for (auto kv : m_components)
		{
			if (kv.first == typeid(T))
			{
				return std::dynamic_pointer_cast<T>(kv.second);
			}
		}

		return std::shared_ptr<T>();
	}
	
	template<typename T>
	const Ref<T> GetComponent() const
	{
		static_assert(std::is_base_of<Component, T>::value, "T is not a component");

		for (auto kv : m_components)
		{
			if (kv.first == typeid(T))
			{
				return std::dynamic_pointer_cast<T>(kv.second);
			}
		}
	
		return std::shared_ptr<T>();
	}

	protected:
		Transform m_transform;
		bool      m_isColliding;
		std::unordered_map<std::type_index, Ref<Component>> m_components;;
	};
}

