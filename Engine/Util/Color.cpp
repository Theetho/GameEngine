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
	Color Color::Wood(167, 103, 38);

	Color::Color(float rgb)
		: Color(rgb, rgb, rgb)
	{}

	Color::Color(float r, float g, float b, float a)
		: glm::vec4(r, g, b, a)
	{
		Clip(x); Clip(y); Clip(z); Clip(w);
	}

	Color::Color(int r,	int g, int b, int a)
		: glm::vec4(0.0)
	{
		Clip(r, x);	Clip(g, y);	Clip(b, z); Clip(a, w);
	}

	Color::Color(int rgb)
		: Color(rgb, rgb, rgb)
	{}
	
	Color::Color(const Color& color)
		: Color(color.r, color.g, color.b, color.a)
	{}
	
	Color::Color(const Color&& color) noexcept
		: Color(color.r, color.g, color.b, color.a)
	{}

	Color::Color(const ImVec4 & imgui_color)
		: Color(imgui_color.x, imgui_color.y, imgui_color.z, imgui_color.w)
	{}

	Color::Color(const ImVec4&& imgui_color) noexcept
		: Color(imgui_color.x, imgui_color.y, imgui_color.z, imgui_color.w)
	{}

	Color::Color(const aiColor4D & ai_color)
		: Color(ai_color.r, ai_color.g, ai_color.b, ai_color.a)
	{}

	Color::Color(const aiColor4D&& ai_color) noexcept
		: Color(ai_color.r, ai_color.g, ai_color.b, ai_color.a)
	{}

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

	Color& Color::operator=(const ImVec4& imgui_color)
	{
		r = imgui_color.x;
		g = imgui_color.y;
		b = imgui_color.z;
		a = imgui_color.w;

		return *this;
	}

	Color& Color::operator=(const ImVec4&& imgui_color) noexcept
	{
		r = imgui_color.x;
		g = imgui_color.y;
		b = imgui_color.z;
		a = imgui_color.w;

		return *this;
	}

	Color& Color::operator=(const aiColor4D& ai_color)
	{
		r = ai_color.r;
		g = ai_color.g;
		b = ai_color.b;
		a = ai_color.a;

		return *this;
	}

	Color& Color::operator=(const aiColor4D&& ai_color) noexcept
	{
		r = ai_color.r;
		g = ai_color.g;
		b = ai_color.b;
		a = ai_color.a;

		return *this;
	}

	Color Color::operator+(const Color& color) const
	{
		return Color(r + color.r, g + color.g, b + color.b);
	}

	Color Color::operator-(const Color& color) const
	{
		return Color(r - color.r, g - color.g, b - color.b);
	}

	Color Color::operator/(const Color& color) const
	{
		#define check(x) x == 0 ? 1.f : x
		return Color(r / check(color.r), g / check(color.g), b / check(color.b));
	}

	Color Color::operator*(const Color& color) const
	{
		return Color(r * color.r, g * color.g, b * color.b);
	}

	Color Color::operator+(float factor) const
	{
		return Color(r + factor, g + factor, b + factor);
	}

	Color Color::operator-(float factor) const
	{
		return Color(r - factor, g - factor, b - factor);
	}

	Color Color::operator/(float factor) const
	{
		if (!factor)
			return Color::Black;
		return Color(r / factor, g / factor, b / factor);
	}

	Color Color::operator*(float factor) const
	{
		return Color(r * factor, g * factor, b * factor);
	}

	Color::~Color()
	{}

	Color Color::Lerp(const Color& a, const Color& b, float factor)
	{
		return a + (b - a) * factor;
	}

	void Color::Clip(float& field)
	{
		if (field > 1.0)
			field = 1.0;
		else if (field < 0.0)
			field = 0.0;
	}

	void Color::Clip(int value, float& field)
	{
		if (value > 255)
			field = 1.0;
		else if (value < 0)
			field = 0.0;
		else
			field = static_cast<float>(value / 255.0);
	}
}