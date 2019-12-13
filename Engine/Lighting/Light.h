#pragma once

#include "Util/Color.h"
#include "API/OpenGL/OpenGLShader.h"
#include "Include/Maths.h"

namespace Engine
{
	class Light
	{
	public:
		explicit Light(
			const Color& color = Color::White
		);

		virtual ~Light()
		{
		}

		void load(
			Ref<Shader> shader,
			const unsigned int& index
		);

		inline void setColor(
			const Color& color
		)
		{
			m_color = color;
		}

		inline const Color& getColor() const
		{
			return m_color;
		}

		virtual inline const int getID() const = 0;

	private:
		Color m_color;
		
	protected:
		enum class LightID
		{
			None,
			Directional,
			Point,
			Spot
		};

		virtual void loadGLUniforms(
			Ref<OpenGLShader> shader,
			const unsigned int& index
		);
	};
}
