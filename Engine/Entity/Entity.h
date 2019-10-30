#pragma once

#include "Transform.h"
#include "Renderer/Material.h"
#include "Renderer/Texture.h"

namespace Engine
{
	class Entity
	{
	public:
		Entity(
			const Transform& transform = Transform(),
			Material* material = nullptr,
			Texture* texture = nullptr
		);
		
		virtual ~Entity();

		virtual void onUpdate() = 0;

		// Return 'this' so it is possible to 
		// concatenate setters
		inline Entity& setTransform(
			const Transform& transform
		)
		{
			m_transform = transform;
			return *this;
		}

		// Return 'this' so it is possible to 
		// concatenate setters
		inline Entity& setMaterial(
			Material* material
		)
		{
			m_material = material;
			return *this;
		}

		// Return 'this' so it is possible to 
		// concatenate setters
		inline Entity& setTexture(
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

	private:
		Transform m_transform;
		Material* m_material;
		Texture*  m_texture;
	};
}

