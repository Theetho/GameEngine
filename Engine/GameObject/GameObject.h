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
			const Transform& transform = Transform(),
			Material* material = nullptr,
			Texture* texture = nullptr
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

		// Return 'this' so it is possible to 
		// concatenate setters
		inline GameObject& setTransform(
			const Transform& transform
		)
		{
			m_transform = transform;
			return *this;
		}

		// Return 'this' so it is possible to 
		// concatenate setters
		inline GameObject& setMaterial(
			Material* material
		)
		{
			m_material = material;
			return *this;
		}

		// Return 'this' so it is possible to 
		// concatenate setters
		inline GameObject& setTexture(
			Texture* texture
		)
		{
			m_texture = texture;
			return *this;
		}

		inline Transform& getTransform()
		{
			return m_transform;
		}

		inline Material* getMaterial()
		{
			if (m_material)
				return m_material;
		}

		inline Texture* getTexture()
		{
			if (m_texture)
			return m_texture;
		}

		inline const Transform& getTransform() const
		{
			return m_transform;
		}

		inline const Material* getMaterial() const
		{
			if (m_material)
				return m_material;
		}

		inline const Texture* getTexture() const
		{
			if (m_texture)
				return m_texture;
		}

		template<typename T>
		T* getComponent(
		)
		{
			static_assert(std::is_base_of<Component, T>::value, "T is not a component");
			T tmp;
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
			T tmp;
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
		Material* m_material;
		Texture*  m_texture;

		std::vector<Component*> m_components;
	};
}

