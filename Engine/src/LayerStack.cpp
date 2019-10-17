#include "EnginePch.h"
#include "LayerStack.h"

namespace Engine
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
	}
	void LayerStack::push(Layer* layer)
	{
		m_stack.push_back(layer);
		layer->onAttach();
	}
	void LayerStack::pop()
	{
		Layer* layer = m_stack.back();
		m_stack.pop_back();
		layer->onDetach();
	}
}