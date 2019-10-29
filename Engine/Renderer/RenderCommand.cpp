#include "EnginePch.h"
#include "RenderCommand.h"

namespace Engine
{
	RendererAPI* RenderCommand::s_renderer = new OpenGLRenderer();

	void RenderCommand::setClearColor(
		const Color& color
	)
	{
		s_renderer->setClearColor(color);
	}
	
	void RenderCommand::clear()
	{
		s_renderer->clear();
	}
	
	void RenderCommand::drawIndexed(
		const Ref<VertexArray>& vao
	)
	{
		s_renderer->drawIndexed(vao);
	}
}