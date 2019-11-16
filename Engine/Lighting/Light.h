#pragma once

#include "Util/Color.h"
#include "Renderer/Shader.h"
#include "Maths.h"

namespace Engine
{
	class Light
	{
	public:
		explicit Light(
			const Color& color    = Color::White,
			const float& ambient  = 0.5f,
			const float& diffuse  = 0.8f,
			const float& specular = 1.0f
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

		inline void setAmbient(
			const float& ambient
		)
		{
			m_ambient = ambient;
		}

		inline void setDiffuse(
			const float& diffuse
		)
		{
			m_diffuse = diffuse;
		}

		inline void setSpecular(
			const float& specular
		)
		{
			m_specular = specular;
		}

		inline const Color& getColor() const
		{
			return m_color;
		}

		inline const float& getAmbient() const
		{
			return m_ambient;
		}

		inline const float& getDiffuse() const
		{
			return m_diffuse;
		}

		inline const float& getSpecular() const
		{
			return m_specular;
		}

		virtual inline const int getID() const = 0;

	private:
		Color m_color;
		float m_ambient;
		float m_diffuse;
		float m_specular;

	protected:
		enum class LightID
		{
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
