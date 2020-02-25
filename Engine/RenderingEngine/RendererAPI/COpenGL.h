#pragma once

#include "CRendererAPI.h"

namespace Engine
{
	class COpenGLRenderer : public CRendererAPI
	{
	public:
		// Inherited from RendererAPI
		void _Clear() const override;
		void _Draw(VertexArray* vertex_array) const override;
		void _Draw(Ref<VertexArray> vertex_array) const override;
		void _SetClearColor(const Color& color) const override;
		void _SetViewport(unsigned int width, unsigned int height) const override;
		int  _GetMaxTextureUnits() const override;
	private:
		// Inheritated from RendererAPI
		unsigned int _GetDrawMode() const override;
	};
}

