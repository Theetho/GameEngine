#pragma once

#include "glm/glm.hpp"

namespace Engine
{
	class Color : public glm::vec4
	{
	public:
		explicit Color(
			const float& r,
			const float& g,
			const float& b,
			const float& a = 1.0
		);
		explicit Color(
			const int& r,
			const int& g,
			const int& b,
			const int& a = 255
		);
		explicit Color(
			const float& rgb = 0.0
		);
		explicit Color(
			const int& rgb = 0
		);
		Color(
			const Color& color
		);
		Color(
			const Color&& color
		) noexcept;
		~Color()
		{
		}

		Color& operator=(
			const Color& color
		);

		Color& operator=(
			const Color&& color
		) noexcept;

		static Color White;
		static Color Silver;
		static Color Gray;
		static Color Black;
		static Color Red;
		static Color Maroon;
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

	private:
		void clip(
			float& field
		);
		void clip(
			const int& value,
			float& field
		);
	};
}

