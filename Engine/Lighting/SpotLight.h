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
			const Color& color = Color::White
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

		virtual inline const int getID() const
		{
			return static_cast<int>(LightID::Spot);
		}

	private:
		float m_cutOff;
		Vec3  m_direction;

		void loadGLUniforms(
			Ref<OpenGLShader> shader,
			const unsigned int& index
		) override;
	};
}

