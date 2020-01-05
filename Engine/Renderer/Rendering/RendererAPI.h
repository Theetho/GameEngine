#pragma once

#include "Util/Color.h"

namespace Engine
{
	enum class API
	{
		None,
		OpenGL
	};

	class VertexArray;

	class RendererAPI
	{
	public:
		virtual ~RendererAPI();

		virtual void Clear() = 0;
		virtual void DrawIndexed(const VertexArray& vertex_array) = 0;

		virtual void SetViewport(unsigned int width, unsigned int height) = 0;
		virtual void SetClearColor(const Color& color) = 0;

		static API sApi;
	};
}

