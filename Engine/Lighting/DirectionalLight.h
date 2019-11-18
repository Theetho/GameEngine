#pragma once

#include "Light.h"

namespace Engine
{
	class DirectionalLight : public Light
	{
	public:
		DirectionalLight(
			const Vec3& direction,
			const Color& color = Color::White
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

		virtual inline const int getID() const
		{
			return static_cast<int>(LightID::Directional);
		}


	private:
		Vec3 m_direction;

		void loadGLUniforms(
			Ref<OpenGLShader> shader,
			const unsigned int& index
		) override;
	};
}