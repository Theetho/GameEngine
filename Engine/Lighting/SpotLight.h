#pragma once
#include "PointLight.h"

namespace Engine
{
	class SpotLight : public PointLight
	{
	public:
		SpotLight(
			const Vec3& position,
			const Vec3& direction,
			const float& cutOff = 12.5f,
			const Attenuation& attenuation = Attenuation(),
			const Color& color = Color::White,
			const float& ambient = 0.5f,
			const float& diffuse = 0.8f,
			const float& specular = 1.0f
		);

		~SpotLight(){}

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

		inline const float& getCutOff() const
		{
			return m_cutOff;
		}

	private:
		float m_cutOff;
		Vec3  m_direction;

		void loadGLUniforms(
			Ref<OpenGLShader> shader
		);
	};
}

