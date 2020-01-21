#pragma once

#include "Renderer/Rendering/RendererAPI.h"

namespace Engine
{
	class OpenGLRenderer : public RendererAPI
	{
	public:
		OpenGLRenderer();
		~OpenGLRenderer();

		void Clear() override;
		void Draw(const VertexArray& vertex_array) override;

		void SetDrawMode(DrawMode draw_mode) override;
		void SetViewport(unsigned int width, unsigned int height) override;
		void SetClearColor(const Color& color) override;
	private:
		unsigned int TranslateDrawMode() override;
	};
}

