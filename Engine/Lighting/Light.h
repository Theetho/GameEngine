#pragma once

namespace Engine
{
	class Color;
	class Shader;
	namespace OpenGL
	{
		class Shader;
	}

	class Light
	{
	public:
		explicit Light(const Color& color = Color::White);
		virtual ~Light();

		virtual void Load(Ref<Shader> shader, unsigned int index);

		virtual int GetID() const = 0;
		virtual const Color& GetColor() const;

		virtual void SetColor(const Color& color);
	private:
		Color mColor;
	protected:
		enum class LightID
		{
			None,
			Directional,
			Point,
			Spot
		};

		virtual void LoadGLUniforms(Ref<OpenGL::Shader> shader, unsigned int index);
	};
}
