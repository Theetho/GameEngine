#pragma once

#include "../Buffer/VertexArray.h"
#include "Util/Color.h"
#include "../Shader.h"
#include "GameObject/Transform.h"

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

		virtual void setViewport(
			const unsigned int& width,
			const unsigned int& height
		) = 0;

		virtual void setClearColor(
			const Color& color
		) = 0;
		virtual void clear() = 0;

		virtual void drawIndexed(
			const Ref<VertexArray>& vao
		) = 0;

	public:
		static API s_api;
	};

	class OpenGLRenderer : public RendererAPI
	{
	public:
		OpenGLRenderer();
		
		~OpenGLRenderer();

		virtual inline void setViewport(
			const unsigned int& width,
			const unsigned int& height
		) override
		{
			glViewport(0, 0, width, height);
		}

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
			const Ref<VertexArray>& vao
		) override
		{
			glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
		}
	};
}

