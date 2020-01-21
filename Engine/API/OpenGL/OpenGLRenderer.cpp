#include "EnginePch.h"
#include "OpenGLRenderer.h"
#include "Renderer/Buffer.h"

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
	
	void OpenGLRenderer::Draw(const VertexArray& vertex_array)
	{
		if (vertex_array.IsIndexed())
			glDrawElements(TranslateDrawMode(), vertex_array.GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		else
			glDrawArrays(TranslateDrawMode(), 0, vertex_array.GetVertexBuffers()[0]->GetCount());
	}
	
	void OpenGLRenderer::SetDrawMode(DrawMode draw_mode)
	{
		mDrawMode = draw_mode;
	}

	void OpenGLRenderer::SetViewport(unsigned int width, unsigned int height)
	{
		glViewport(0, 0, width, height);
	}
	
	void OpenGLRenderer::SetClearColor(const Color& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
	
	unsigned int OpenGLRenderer::TranslateDrawMode()
	{
		switch (mDrawMode)
		{
			case Engine::DrawMode::TRIANGLE:
				return GL_TRIANGLES; break;
			case Engine::DrawMode::TRIANGLE_STRIP:
				return GL_TRIANGLE_STRIP; break;
			default:
				return GL_TRIANGLES; break;
		}
	}
}