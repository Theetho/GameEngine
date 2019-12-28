#pragma once

#include "glm/glm.hpp"

namespace Engine
{
	class Color : public glm::vec4
	{
	public:
		explicit Color(float r, float g, float b, float a = 1.0);
		explicit Color(int r, int g, int b, int a = 255);
		explicit Color(float rgb = 0.0);
		explicit Color(int rgb = 0);
		Color(const Color& color);
		Color(const Color&& color) noexcept;
		Color& operator=(const Color& color);
		Color& operator=(const Color&& color) noexcept;
		~Color();

		static Color White;
		static Color Silver;
		static Color Gray;
		static Color Black;
		static Color Red;
		static Color Maroon;
		static Color Brown;
		static Color Yellow;
		static Color Olive;
		static Color Green;
		static Color DarkGreen;
		static Color Aqua;
		static Color Teal;
		static Color Blue;
		static Color Navy;
		static Color Fuchsia;
		static Color Purple;
		static Color Sand;
		static Color Wood;

	private:
		void Clip(float& field);
		void Clip(int value, float& field);
	};
}

