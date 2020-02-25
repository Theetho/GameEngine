#include "EnginePch.h"
#include "OpenGL.h"
#include "Renderer/Buffer.h"

namespace Engine
{
	namespace OpenGL
	{
		void Renderer::Clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Renderer::Draw(VertexArray* vertex_array) const
		{
			if (vertex_array->IsIndexed())
				glDrawElements(GetDrawMode(), vertex_array->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
			else
				glDrawArrays(GetDrawMode(), 0, vertex_array->GetVertexBuffers()[0]->GetCount());
		}

		void Renderer::Draw(Ref<VertexArray> vertex_array) const
		{
			if (vertex_array->IsIndexed())
				glDrawElements(GetDrawMode(), vertex_array->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
			else
				glDrawArrays(GetDrawMode(), 0, vertex_array->GetVertexBuffers()[0]->GetCount());
		}

		void Renderer::SetClearColor(const Color& color) const
		{
			glClearColor(color.r, color.g, color.b, color.a);
		}

		void Renderer::SetViewport(unsigned int width, unsigned int height) const
		{
			glViewport(0, 0, width, height);
		}

		int Renderer::GetMaxTextureUnits() const
		{
			int result = 1;
			glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &result);
		
			return result;
		}

		unsigned int Renderer::GetDrawMode() const
		{
			switch (mDrawMode)
			{
				case Engine::DrawMode::DEFAULT:
					return GL_TRIANGLES; break;
				case Engine::DrawMode::TRIANGLES:
					return GL_TRIANGLES; break;
				case Engine::DrawMode::TRIANGLE_STRIP:
					return GL_TRIANGLE_STRIP; break;
				case Engine::DrawMode::PATCHES:
					return GL_PATCHES; break;
				default:
					return GL_TRIANGLES; break;
			}
		}
	}
}