#pragma once

namespace Engine
{

/// Abstract base class

	class GraphicsContext
	{
	public:
		virtual void initialize() = 0;
		
		virtual void swapBuffers() = 0;
	};
}