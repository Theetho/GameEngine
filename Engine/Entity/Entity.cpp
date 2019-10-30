#include "EnginePch.h"
#include "Entity.h"

namespace Engine
{
	Entity::Entity(
		const Transform& transform,
		Material* material,
		Texture* texture
	)
		: m_transform(transform)
		, m_material(material)
		, m_texture(texture)
	{
	}

	Entity::~Entity()
	{
	}
}