#include "EnginePch.h"
#include "Renderer.h"
#include "Renderer/Buffer.h"

namespace Engine
{
	namespace OpenGL
	{
		Renderer::Renderer()
			: Engine::RendererAPI()
		{
			sApi = API::OpenGL;
		}

		Renderer::~Renderer()
		{
		}

		void Renderer::Clear()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Renderer::Draw(const VertexArray& vertex_array)
		{
			if (vertex_array.IsIndexed())
				glDrawElements(TranslateDrawMode(), vertex_array.GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
			else
				glDrawArrays(TranslateDrawMode(), 0, vertex_array.GetVertexBuffers()[0]->GetCount());
		}

		void Renderer::SetDrawMode(DrawMode draw_mode)
		{
			mDrawMode = draw_mode;
		}

		void Renderer::SetViewport(unsigned int width, unsigned int height)
		{
			glViewport(0, 0, width, height);
		}

		void Renderer::SetClearColor(const Color& color)
		{
			glClearColor(color.r, color.g, color.b, color.a);
		}

		unsigned int Renderer::TranslateDrawMode()
		{
			switch (mDrawMode)
			{
				case Engine::DrawMode::DEFAULT:
					return GL_TRIANGLES; break;
				case Engine::DrawMode::TRIANGLE:
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