#pragma once

#include "Renderer/Rendering/RendererAPI.h"

namespace Engine
{
	namespace OpenGL
	{
		class Renderer : public Engine::RendererAPI
		{
		public:
			Renderer();
			~Renderer();

			void Clear() override;
			void Draw(const VertexArray& vertex_array, uint indice_count) override;

			void SetDrawMode(DrawMode draw_mode) override;
			void SetViewport(unsigned int width, unsigned int height) override;
			void SetClearColor(const Color& color) override;
		private:
			unsigned int TranslateDrawMode() override;
		};
	}
}

