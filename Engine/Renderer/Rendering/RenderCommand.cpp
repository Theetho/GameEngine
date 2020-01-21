#include "EnginePch.h"
#include "RenderCommand.h"
#include "API/OpenGL/OpenGLRenderer.h"

namespace Engine
{
	RendererAPI* RenderCommand::sRenderer = new OpenGLRenderer();

	void RenderCommand::SetDrawMode(DrawMode draw_mode)
	{
		sRenderer->SetDrawMode(draw_mode);
	}

	API RenderCommand::GetAPI()
	{
		return RendererAPI::sApi;
	}

	void RenderCommand::SetViewport(unsigned int width, unsigned int height)
	{
		sRenderer->SetViewport(width, height);
	}

	void RenderCommand::SetClearColor(const Color& color)
	{
		sRenderer->SetClearColor(color);
	}
	
	void RenderCommand::Clear()
	{
		sRenderer->Clear();
	}
	
	void RenderCommand::Draw(const VertexArray& vertex_array)
	{
		sRenderer->Draw(vertex_array);
	}

	void RenderCommand::Draw(Ref<VertexArray> vertex_array)
	{
		sRenderer->Draw(*vertex_array);
	}
}