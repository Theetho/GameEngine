#pragma once

#include "Export.h"
#include "Layer.h"

namespace Engine
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void push(Layer* layer);
		void pop();

		inline std::vector<Layer*>::iterator begin() { return m_stack.begin(); }
		inline std::vector<Layer*>::iterator end() { return m_stack.end(); }

	private:
		std::vector<Layer*>			  m_stack;
		std::vector<Layer*>::iterator m_insert;
	};
}