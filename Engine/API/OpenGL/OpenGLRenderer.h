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
		void DrawIndexed(const VertexArray& vertex_array) override;

		void SetViewport(unsigned int width, unsigned int height) override;
		void SetClearColor(const Color& color) override;
	};
}

