#pragma once

#include "Light.h"

namespace Engine
{
	class DirectionalLight : public Light
	{
	public:
		DirectionalLight(
			const Vec3& direction,
			const Color& color    = Color::White,
			const float& ambient  = 0.5f,
			const float& diffuse  = 0.8f,
			const float& specular = 1.0f
		);

		~DirectionalLight()
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

	private:
		Vec3 m_direction;

		void loadGLUniforms(
			Ref<OpenGLShader> shader
		);
	};
}