#pragma once

#include "../Renderer/Rendering/Renderable.h"

namespace Engine
{
	class Font;
	class VertexArray;

	class Text : public Renderable
	{
	public:
		Text();
		Text(const std::string& label, const Vec2& position, const Color& color = Color::White);
		Text(const Text& other);
		Text(const Text&& other);
		Text& operator=(const Text& other);
		Text& operator=(const Text&& other);
		static void SetGlobalFont(Font* font);
	private:
		static Font* sFont;
		std::string mLabel;
		Vec3 mPosition;
		Color mColor;
		Ref<VertexArray> mVertexArray;

		void InitializeVertices();
		void AddVertice(std::vector<float>& vertices, float x, float y, float u, float v);
		// Change black color to rgb(1, 1, 1),
		// because rgb(0, 0, 0) is the background
		void CheckColor();
		virtual void Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const override;
	};
}

