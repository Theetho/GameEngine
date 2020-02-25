#pragma once

#include "RendererAPI.h"

namespace Engine
{
	namespace OpenGL
	{
		class Renderer : public CRendererAPI
		{
		public:
			// Inherited from RendererAPI
			void Clear() const override;
			void Draw(VertexArray* vertex_array) const override;
			void Draw(Ref<VertexArray> vertex_array) const override;
			void SetClearColor(const Color& color) const override;
			void SetViewport(unsigned int width, unsigned int height) const override;
			int GetMaxTextureUnits() const override;
		private:
			// Inheritated from RendererAPI
			unsigned int GetDrawMode() const override;
		};
	}
}

