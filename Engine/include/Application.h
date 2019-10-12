#pragma once

#include "Export.h"

namespace Engine
{
	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();
		virtual void run();
	};

	// Has to be define by the game
	Application* createApplication();
}