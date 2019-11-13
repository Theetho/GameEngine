#include "EnginePch.h"
#include "DirectionalLight.h"

namespace Engine
{
	DirectionalLight::DirectionalLight(
		const Vec3&  direction, 
		const Color& color, 
		const float& ambient, 
		const float& diffuse, 
		const float& specular
	)
		: Light(color, ambient, diffuse, specular)
		, m_direction(direction)
	{
	}
}