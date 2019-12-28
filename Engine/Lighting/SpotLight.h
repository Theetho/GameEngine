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
			float cut_off = 12.5f,
			const Attenuation& attenuation = Attenuation(),
			const Color& color = Color::White
		);
		~SpotLight();

		int			GetID() const override;
		float		GetCutOff() const;
		const Vec3& GetDirection() const;

		void SetDirection(const Vec3& direction)
		{
			mDirection = direction;
		}
	private:
		float mCutOff;
		Vec3  mDirection;

		void LoadGLUniforms(Ref<OpenGLShader> shader, unsigned int index) override;
	};
}

