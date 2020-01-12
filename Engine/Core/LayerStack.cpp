#include "EnginePch.h"
#include "LayerStack.h"
#include "Layer.h"

namespace Engine
{
	LayerStack::LayerStack()
	{}

	LayerStack::~LayerStack()
	{}
	
	void LayerStack::Push(Layer* layer)
	{
		mStack.push_back(layer);
		layer->OnAttach();
	}
	
	void LayerStack::Pop()
	{
		Layer* layer = mStack.back();
		mStack.pop_back();
		layer->OnDetach();
	}

	bool LayerStack::IsEmpty() const
	{
		return !mStack.size();
	}
}