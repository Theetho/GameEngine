#include "EnginePch.h"
#include "OpenGLRenderer.h"
#include "Renderer/Buffer/VertexArray.h"

namespace Engine
{
	OpenGLRenderer::OpenGLRenderer()
	{
		sApi = API::OpenGL;
	}

	OpenGLRenderer::~OpenGLRenderer()
	{}

	void OpenGLRenderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	void OpenGLRenderer::DrawIndexed(const VertexArray& vertex_array)
	{
		glDrawElements(GL_TRIANGLES, vertex_array.GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
	
	void OpenGLRenderer::SetViewport(unsigned int width, unsigned int height)
	{
		glViewport(0, 0, width, height);
	}
	
	void OpenGLRenderer::SetClearColor(const Color& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
}