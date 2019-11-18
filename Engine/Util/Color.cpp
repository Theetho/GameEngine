#include "EnginePch.h"
#include "Color.h"

namespace Engine
{
	Color Color::White(1.0f, 1.0f, 1.0f);
	Color Color::Silver(0.75f, 0.75f, 0.75f);
	Color Color::Gray(0.5f, 0.5f, 0.5f);
	Color Color::Black(0.0f, 0.0f, 0.0f);
	Color Color::Red(1.0f, 0.0f, 0.0f);
	Color Color::Maroon(0.4f, 0.2f, 0.1f);
	Color Color::Yellow(1.0f, 1.0f, 0.0f);
	Color Color::Olive(0.5f, 0.5f, 0.0f);
	Color Color::Green(0.0f, 1.0f, 0.0f);
	Color Color::DarkGreen(0.0f, 0.5f, 0.0f);
	Color Color::Aqua(0.0f, 1.0f, 1.0f);
	Color Color::Teal(0.0f, 0.5f, 0.5f);
	Color Color::Blue(0.0f, 0.0f, 1.0f);
	Color Color::Navy(0.0f, 0.0f, 0.5f);
	Color Color::Fuchsia(1.0f, 0.0f, 1.0f);
	Color Color::Purple(0.5f, 0.0f, 0.5f);
	Color Color::Brown(91, 60, 17);
	Color Color::Sand(253, 241, 184);

	Color::Color(
		const float& r,
		const float& g,
		const float& b,
		const float& a
	)
		: glm::vec4(r, g, b, a)
	{
		clip(this->x);
		clip(this->y);
		clip(this->z);
		clip(this->w);
	}
	Color::Color(
		const int& r,
		const int& g,
		const int& b,
		const int& a
	)
		: glm::vec4(0.0)
	{
		clip(r, x);
		clip(g, y);
		clip(b, z);
		clip(a, w);
	}

	Color::Color(
		const float& rgb
	)
		: Color(rgb, rgb, rgb)
	{
	}

	Color::Color(
		const int& rgb
	)
		: Color(rgb, rgb, rgb)
	{
	}
	
	Color::Color(
		const Color& color
	)
		: Color(color.r, color.g, color.b, color.a)
	{
	}
	
	Color::Color(
		const Color&& color
	) noexcept
		: Color(color.r, color.g, color.b, color.a)
	{
	}

	Color& Color::operator=(const Color& color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;

		return *this;
	}

	Color& Color::operator=(const Color&& color) noexcept
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;

		return *this;
	}

	void Color::clip(
		float& field
	)
	{
		if (field > 1.0)
			field = 1.0;
		else if (field < 0.0)
			field = 0.0;
	}

	void Color::clip(
		const int& value,
		float& field
	)
	{
		if (value > 255)
			field = 1.0;
		else if (value < 0)
			field = 0.0;
		else
			field = static_cast<float>(value / 255.0);
	}
}