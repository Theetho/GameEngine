#pragma once

#include "Light.h"

namespace Engine
{
	class DirectionalLight : public Light
	{
	public:
		DirectionalLight(const Vec3& direction, const Color& color = Color::White);
		~DirectionalLight();

		virtual int GetID() const override;
		const Vec3& GetDirection() const;

		void SetDirection(const Vec3& direction);
	private:
		Vec3 mDirection;

		void LoadGLUniforms(Ref<OpenGLShader> shader, unsigned int index) override;
	};
}