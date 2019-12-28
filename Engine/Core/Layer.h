#pragma once

#include "Event.h"

namespace Engine
{
	class Layer
	{
	public:
		virtual ~Layer()
		{}

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnUpdate(const double& delta) = 0;
		virtual void OnEvent(Event& event) = 0;
	};
};

