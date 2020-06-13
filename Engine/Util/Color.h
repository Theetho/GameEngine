#pragma once

namespace Engine
{
	// Color are always returned with fields between
	// 0.0 and 1.0 (But can be created with int between
	// 0 and 255)
	class Color : public Vec4
	{
	public:
		Color(float rgb = 0.0);
		explicit Color(float r, float g, float b, float a = 1.0);
		explicit Color(int r, int g, int b, int a = 255);
		explicit Color(int rgb);
		Color(const Color& color);
		Color(const Color&& color) noexcept;
		Color(const ImVec4& imgui_color);
		Color(const ImVec4&& imgui_color) noexcept;
		Color& operator=(const Color& color);
		Color& operator=(const Color&& color) noexcept;
		Color& operator=(const ImVec4& imgui_color);
		Color& operator=(const ImVec4&& imgui_color) noexcept;
		Color operator+(const Color& color) const;
		Color operator-(const Color& color) const;
		Color operator/(const Color& color) const;
		Color operator*(const Color& color) const;
		Color operator+(float factor) const;
		Color operator-(float factor) const;
		Color operator/(float factor) const;
		Color operator*(float factor) const;
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

		static Color Lerp(const Color& a, const Color& b, float factor);

	private:
		void Clip(float& field);
		void Clip(int value, float& field);
	};
}


