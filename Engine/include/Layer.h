#pragma once

#include "Export.h"
#include "Event.h"

namespace Engine
{
	class ENGINE_API Layer
	{
	public:
		Layer();
		~Layer();

		virtual void onAttach();
		virtual void onDetach();
		virtual void onUpdate(const double& delta);
		virtual void onEvent(Event& event);
	};
};

