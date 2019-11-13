#include "EnginePch.h"
#include "Light.h"

namespace Engine
{
	Light::Light(
		const Color& color,
		const float& ambient,
		const float& diffuse,
		const float& specular
	)
		: m_color(color)
		, m_ambient	(ambient)
		, m_diffuse(diffuse)
		, m_specular(specular)
	{
	}
}