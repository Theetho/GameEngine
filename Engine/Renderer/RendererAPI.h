#pragma once

#include "VertexArray.h"
#include "Util/Color.h"

namespace Engine
{
	enum class API
	{
		None,
		OpenGL
	};

	class RendererAPI
	{
	public:
		virtual ~RendererAPI()
		{
		}

		virtual void setClearColor(
			const Color& color
		) = 0;
		virtual void clear() = 0;

		virtual void drawIndexed(
			const std::shared_ptr<VertexArray>& vao
		) = 0;
	public:
		static API s_api;
	};

	class OpenGLRenderer : public RendererAPI
	{
	public:
		OpenGLRenderer();
		
		~OpenGLRenderer();

		inline void setClearColor(
			const Color& color
		) override
		{
			glClearColor(color.r, color.g, color.b, color.a);
		}
		
		inline void clear() override
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		
		inline void drawIndexed(
			const std::shared_ptr<VertexArray>& vao
		) override
		{
			glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
		}
	};
}

