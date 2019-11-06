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
		GameObject(
			const Transform& transform = Transform()
		);
		
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

		template<typename T>
		T* getComponent(
		)
		{
			static_assert(std::is_base_of<Component, T>::value, "T is not a component");
			T tmp(nullptr);
			std::string name = tmp.getName();
			for (auto component : m_components)
			{
				if (component->getName() == name)
					return static_cast<T*>(component);
			}

			return nullptr;
		}

		template<typename T>
		const T* getComponent(
		) const
		{
			static_assert(std::is_base_of<Component, T>::value, "T is not a component");
			T tmp(nullptr);
			std::string name = tmp.getName();
			for (auto component : m_components)
			{
				if (component->getName() == name)
					return static_cast<T*>(component);
			}

			return nullptr;
		}

	protected:
		Transform m_transform;
		bool      m_isColliding;
		std::vector<Component*> m_components;
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

