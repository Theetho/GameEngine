#pragma once

namespace Engine
{
/// Abstract base class
	class GraphicsContext
	{
	public:
		virtual void Initialize() = 0;
		virtual void SwapBuffers() = 0;
	};
}