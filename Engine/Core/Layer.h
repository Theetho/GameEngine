#pragma once

#include "Event.h"

namespace Engine
{
	class Layer
	{
	public:
		virtual ~Layer()
		{
		}

		virtual void onAttach() = 0;

		virtual void onDetach() = 0;

		virtual void onUpdate(
			const double& delta
		) = 0;

		virtual void onEvent(
			Event& event
		) = 0;
	};
};

