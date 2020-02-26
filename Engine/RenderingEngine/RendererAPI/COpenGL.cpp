#include "EnginePch.h"
#include "COpenGL.h"
#include "Renderer/Buffer.h"

namespace Engine
{
	void COpenGLRenderer::_Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void COpenGLRenderer::_Draw(VertexArray* vertex_array) const
	{
		_Draw(vertex_array, vertex_array->GetIndexBuffer()->GetCount());
	}

	void COpenGLRenderer::_Draw(Ref<VertexArray> vertex_array) const
	{
		_Draw(vertex_array, vertex_array->GetIndexBuffer()->GetCount());
	}

	void COpenGLRenderer::_Draw(VertexArray* vertex_array, uint indices_count) const
	{
		if (vertex_array->IsIndexed())
			glDrawElements(_GetDrawMode(), indices_count, GL_UNSIGNED_INT, nullptr);
		else
			glDrawArrays(_GetDrawMode(), 0, vertex_array->GetVertexBuffers()[0]->GetCount());
	}

	void COpenGLRenderer::_Draw(Ref<VertexArray> vertex_array, uint indices_count) const
	{
		if (vertex_array->IsIndexed())
		{
			glDrawElements(_GetDrawMode(), indices_count, GL_UNSIGNED_INT, nullptr);
		}
		else
			glDrawArrays(_GetDrawMode(), 0, vertex_array->GetVertexBuffers()[0]->GetCount());
	}

	void COpenGLRenderer::_SetClearColor(const Color& color) const
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void COpenGLRenderer::_SetViewport(unsigned int width, unsigned int height) const
	{
		glViewport(0, 0, width, height);
	}

	int COpenGLRenderer::_GetMaxTextureUnits() const
	{
		int result = 1;
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &result);
		
		return result;
	}

	unsigned int COpenGLRenderer::_GetDrawMode() const
	{
		switch (_mDrawMode)
		{
			case Engine::CDrawMode::DEFAULT:
				return GL_TRIANGLES; break;
			case Engine::CDrawMode::TRIANGLES:
				return GL_TRIANGLES; break;
			case Engine::CDrawMode::TRIANGLE_STRIP:
				return GL_TRIANGLE_STRIP; break;
			case Engine::CDrawMode::PATCHES:
				return GL_PATCHES; break;
			default:
				return GL_TRIANGLES; break;
		}
	}
}