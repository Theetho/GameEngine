#pragma once

#include "Layer.h"

namespace Engine
{
	class LayerStack
	{
	public:
		LayerStack();

		~LayerStack();

		void push(
			Layer* layer
		);

		void pop();

		inline bool isEmpty() const
		{
			return !m_stack.size();
		}

		std::vector<Layer*>::iterator begin() 
		{ 
			return m_stack.begin();
		}
		std::vector<Layer*>::iterator end()
		{
			return m_stack.end(); 
		}

	private:
		std::vector<Layer*>	m_stack;
		unsigned int		m_insert = 0;
	};
}